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

        // Step 2: Get the number of groups
        unsigned int groupCount = parser.getGroupCount();
        if (groupCount == 0) {
          throw std::runtime_error("No groups found in TDMS file.");
        }

        // Calculate the total number of channels across all groups
        unsigned int totalChannels = 0;
        for (unsigned int i = 0; i < groupCount; i++) {
            TdmsGroup *group = parser.getGroup(i);
            if (group) {
                totalChannels += group->getGroupSize();
            }
        }

        // Step 3: Allocate the DenseMatrix if it's not already allocated
        if (res == nullptr) {
          res = DataObjectFactory::create<DenseMatrix<VT>>(numRows, numCols, false);
        }

        // Step 4: Populate the DenseMatrix with the channel data from all groups
        VT* valuesRes = res->getValues();  // Get the raw pointer to the matrix values
        size_t currentChannel = 0; // Track the current column in the matrix

        for (unsigned int i = 0; i < groupCount; i++) {
          TdmsGroup *group = parser.getGroup(i);
          if (!group) {
            throw std::runtime_error("Error retrieving group " + std::to_string(i));
          }

          // Get the number of channels in this group
          unsigned int channelsCount = group->getGroupSize();
          if (channelsCount == 0) {
            continue; // Skip empty groups
          }

          // Step 5: Iterate over each channel in the group
          for (unsigned int j = 0; j < channelsCount; j++) {
            TdmsChannel *ch = group->getChannel(j);
            if (!ch) {
              throw std::runtime_error("Error retrieving channel " + std::to_string(j) + " in group " + std::to_string(i));
            }

            unsigned long long dataCount = ch->getDataCount();
            if (dataCount != numRows) {
              throw std::runtime_error("Mismatch in data size for channel " + std::to_string(j) + " in group " + std::to_string(i));
            }

            // Get the data vector from the channel
            std::vector<double> data = ch->getDataVector();

            // Step 6: Copy the channel data into the matrix
            for (size_t r = 0; r < numRows; r++) {
              size_t index = r * totalChannels + currentChannel; // Calculate the correct position
              valuesRes[index] = static_cast<VT>(data[r]);
            }

            // Move to the next channel (next column in the matrix)
            currentChannel++;
          }
        }

        if (currentChannel != totalChannels) {
          throw std::runtime_error("Error: Number of populated channels doesn't match total channel count.");
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
        //throw std::runtime_error("Error opening TDMS file: " + std::string(filename));
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
        if (res == nullptr) {
          res = DataObjectFactory::create<Frame>(numRows, numCols, schema, nullptr, false);
        }
        uint8_t ** rawCols = new uint8_t * [numCols];
        ValueTypeCode * colTypes = new ValueTypeCode[numCols];
        for(size_t i = 0; i < numCols; i++) {
            rawCols[i] = reinterpret_cast<uint8_t *>(res->getColumnRaw(i));
            colTypes[i] = res->getColumnType(i);
        }
        size_t row ,col,totalcol=0;
        for(unsigned int  i =0 ;i<groupCount;i++){
          TdmsGroup *group = parser.getGroup(i);
        if (!group) {
          throw std::runtime_error("No group found in TDMS file.");
        }
        unsigned int channelsCount = group->getGroupSize();
        if (channelsCount == 0) {
          throw std::runtime_error("No channels found in the TDMS file group.");
        }
        //totalcol+=channelsCount;

        for (col=0 ; col < channelsCount; col++) {
          TdmsChannel *ch = group->getChannel(col);
          if (!ch) {
            throw std::runtime_error("Error retrieving channel " + std::to_string(col));
          }
    
          unsigned long long dataCount = ch->getDataCount();
          if (dataCount != numRows) {
            throw std::runtime_error("Mismatch in data size for channel " + std::to_string(col));
          }
    
          // Get the data vector from the channel
          //std::vector<double> data = ch->getDataVector();
          //size_t pos = 0;
          
          switch (colTypes[totalcol + col]) {
          case ValueTypeCode::SI8:{
            // int8_t val_si8;
            // convertCstr(file->line + pos, &val_si8);
            //std::vector<double> data = ch->getDataVector();
            //for(row =0; row<numRows; row++){
            //  reinterpret_cast<int8_t *>(rawCols[totalcol + col])[row] = data[row];
            //}
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<int8_t *>(rawCols[totalcol + col])[row] = (int8_t)data[row];
            }
            
            break;
          }
          case ValueTypeCode::SI32:{
            //int32_t val_si32;
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<int32_t *>(rawCols[totalcol + col])[row] = (int32_t)data[row];
            }
            //convertCstr(file->line + pos, &val_si32);
            //reinterpret_cast<int32_t *>(rawCols[col])[row] = val_si32;
            break;
          }
            
          case ValueTypeCode::SI64:{
            int64_t val_si64;
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<int64_t *>(rawCols[totalcol + col])[row] = (int64_t)data[row];
            }
            //convertCstr(file->line + pos, &val_si64);
            //reinterpret_cast<int64_t *>(rawCols[col])[row] = val_si64;
            break;
          }
            
          case ValueTypeCode::UI8:{
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<u_int8_t *>(rawCols[totalcol + col])[row] = (u_int8_t)data[row];
            }
            break;
          }
            //uint8_t val_ui8;
            // convertCstr(file->line + pos, &val_ui8);
            // reinterpret_cast<uint8_t *>(rawCols[col])[row] = val_ui8;
            
          case ValueTypeCode::UI32:{
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<u_int32_t *>(rawCols[totalcol + col])[row] = (u_int32_t)data[row];
            }
            break;
          }
            //uint32_t val_ui32;
            // convertCstr(file->line + pos, &val_ui32);
            // reinterpret_cast<uint32_t *>(rawCols[col])[row] = val_ui32;
            
          case ValueTypeCode::UI64:{
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<u_int64_t *>(rawCols[totalcol + col])[row] = (u_int64_t)data[row];
            }
            break;
          }
          
            //uint64_t val_ui64;
            // convertCstr(file->line + pos, &val_ui64);
            // reinterpret_cast<uint64_t *>(rawCols[col])[row] = val_ui64;
            
          case ValueTypeCode::F32:{
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<float *>(rawCols[totalcol + col])[row] = (float)data[row];
            }
            break;
          }
            //float val_f32;
            // convertCstr(file->line + pos, &val_f32);
            // reinterpret_cast<float *>(rawCols[col])[row] = val_f32;
            break;
          case ValueTypeCode::F64:{
            std::vector<double> data = ch->getDataVector();
            for(row =0; row<numRows; row++){
              reinterpret_cast<double *>(rawCols[totalcol + col])[row] = data[row];
            }
            break;
          }
            //double val_f64;
            //convertCstr(file->line + pos, &val_f64);
            //reinterpret_cast<double *>(rawCols[col])[row] = val_f64;
            
          // default:
          //   throw std::runtime_error("ReadCsvFile::apply: unknown value type code");
          }
          //while(file->line[pos] != delim) pos++;
          //pos++; // skip delimiter
  }
  totalcol+=channelsCount;

        }

        // Assume we are working with the first group
        

        // Get the number of channels in the group
        


        

        

        
        
                    }
};
