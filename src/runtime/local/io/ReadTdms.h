/*
 * Copyright 2021 The DAPHNE Consortium
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <runtime/local/datastructures/DataObjectFactory.h>
#include <runtime/local/datastructures/DenseMatrix.h>
#include <runtime/local/datastructures/CSRMatrix.h>
#include <runtime/local/datastructures/Frame.h>

#include <runtime/local/io/File.h>
#include <runtime/local/io/utils.h>
#include <runtime/local/io/ReadCsvFile.h>

#include <util/preprocessor_defs.h>

#include <type_traits>

#include <cstddef>
#include <cstdint>
#include <queue>
#include <fstream>
#include <limits>
#include <sstream>

#include <TdmsParser.h>
#include <TdmsChannel.h>
#include <TdmsGroup.h>

// ****************************************************************************
// Struct for partial template specialization
// ****************************************************************************

template <class DTRes> struct ReadTdms {
  static void apply(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
                    char delim) = delete;

  static void apply(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
                    ssize_t numNonZeros, bool sorted = true) = delete;

  static void apply(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
                    char delim, ValueTypeCode *schema) = delete;
};

// ****************************************************************************
// Convenience function
// ****************************************************************************

template <class DTRes>
void readTdms(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
             char delim) {
  ReadTdms<DTRes>::apply(res, filename, numRows, numCols, delim);
}

template <class DTRes>
void readTdms(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
             char delim, ValueTypeCode *schema) {
  ReadTdms<DTRes>::apply(res, filename, numRows, numCols, delim, schema);
}

template <class DTRes>
void readTdms(DTRes *&res, const char *filename, size_t numRows, size_t numCols,
             char delim, ssize_t numNonZeros, bool sorted = true) {
    ReadTdms<DTRes>::apply(res, filename, numRows, numCols, delim, numNonZeros, sorted);
}

// ****************************************************************************
// (Partial) template specializations for different data/value types
// ****************************************************************************

// ----------------------------------------------------------------------------
// DenseMatrix
// ----------------------------------------------------------------------------

template <typename VT> struct ReadTdms<DenseMatrix<VT>> {
  static void apply(DenseMatrix<VT> *&res, const char *filename, size_t numRows,
                    size_t numCols, char delim) {
        // Step 1: Parse the TDMS file
        TdmsParser parser(filename, true); // true indicates storing the values in memory
        if (parser.fileOpeningError()) {
          throw std::runtime_error("Error opening TDMS file: " + std::string(filename));
        }

        // Read the TDMS file data
        parser.read(false);

        // Step 2: Get the number of groups and channels
        unsigned int groupCount = parser.getGroupCount();
        if (groupCount == 0) {
          throw std::runtime_error("No groups found in TDMS file.");
        }

        // Assume we are working with the first group
        TdmsGroup *group = parser.getGroup(0);
        if (!group) {
          throw std::runtime_error("No group found in TDMS file.");
        }

        // Get the number of channels in the group
        unsigned int channelsCount = group->getGroupSize();
        if (channelsCount == 0) {
          throw std::runtime_error("No channels found in the TDMS file group.");
        }

        // Step 3: Allocate the DenseMatrix
        // numRows is the number of data points in each channel, numCols is the number of channels
        if (res == nullptr) {
          res = DataObjectFactory::create<DenseMatrix<VT>>(numRows, channelsCount, false);
        }

        VT *valuesRes = res->getValues();  // Get the raw pointer to the matrix values
        size_t cell = 0;
    
        // Step 4: Populate the DenseMatrix with the channel data
        for (unsigned int j = 0; j < channelsCount; j++) {
          TdmsChannel *ch = group->getChannel(j);
          if (!ch) {
            throw std::runtime_error("Error retrieving channel " + std::to_string(j));
          }
    
          unsigned long long dataCount = ch->getDataCount();
          if (dataCount != numRows) {
            throw std::runtime_error("Mismatch in data size for channel " + std::to_string(j));
          }
    
          // Get the data vector from the channel
          std::vector<double> data = ch->getDataVector();
    
          // Copy data to the DenseMatrix (each column corresponds to a channel)
          for (size_t r = 0; r < numRows; r++) {
            valuesRes[cell++] = static_cast<VT>(data[r]);  // Store data in the matrix
          }
        }

  }
};

// ----------------------------------------------------------------------------
// CSRMatrix
// ----------------------------------------------------------------------------

template <typename VT> struct ReadTdms<CSRMatrix<VT>> {
    static void apply(CSRMatrix<VT> *&res, const char *filename, size_t numRows,
                      size_t numCols, char delim, ssize_t numNonZeros, bool sorted = true) {
        throw std::runtime_error("Error opening TDMS file: " + std::string(filename));
        // struct File *file = openFile(filename);
        // readCsvFile(res, file, numRows, numCols, delim, numNonZeros, sorted);
        // closeFile(file);
    }
};


// ----------------------------------------------------------------------------
// Frame
// ----------------------------------------------------------------------------

template <> struct ReadTdms<Frame> {
  static void apply(Frame *&res, const char *filename, size_t numRows,
                    size_t numCols, char delim, ValueTypeCode *schema) {
    throw std::runtime_error("Error opening TDMS file: " + std::string(filename));
    // struct File *file = openFile(filename);
    // readCsvFile(res, file, numRows, numCols, delim, schema);
    // closeFile(file);
  }
};
