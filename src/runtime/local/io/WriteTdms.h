#ifndef SRC_RUNTIME_LOCAL_IO_WRITETDMS_H
#define SRC_RUNTIME_LOCAL_IO_WRITETDMS_H

#include <runtime/local/datastructures/DataObjectFactory.h>
#include <runtime/local/datastructures/DenseMatrix.h>
#include <runtime/local/datastructures/Frame.h>

#include <runtime/local/io/File.h>
#include <runtime/local/io/utils.h>

#include <stdexcept>
#include <type_traits>

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <limits>
#include <sstream>
#include <TDMS.h> 
#include <string>

// ****************************************************************************
// Struct for partial template specialization
// ****************************************************************************

template <class DTArg>
struct WriteTdms {
    static void apply(const DTArg *arg, const char *filename) = delete;
};

// ****************************************************************************
// Convenience function
// ****************************************************************************

template <class DTArg>
void writeTdms(const DTArg *arg, const char *filename) {
    WriteTdms<DTArg>::apply(arg, filename);
}

// ****************************************************************************
// (Partial) template specializations for different data/value types
// ****************************************************************************

// ----------------------------------------------------------------------------
// DenseMatrix
// ----------------------------------------------------------------------------

template <typename VT>
struct WriteTdms<DenseMatrix<VT>> {
    static void apply(const DenseMatrix<VT> *arg, const char *filename) {
        // Step 1: Open the TDMS file for writing
        FILE *MyFile = fopen(filename, "wb");
        if (!MyFile) {
            throw std::runtime_error("WriteTdms: File open failed!");
        }

        TDMS_File_t FileTDMS;
        if (TDMS_InitFile(&FileTDMS) != TDMS_OK) {
            fclose(MyFile);
            throw std::runtime_error("WriteTdms: TDMS Init failed!");
        }

        // Step 2: Add a group to the TDMS file
        TDMS_Group_t Group;
        char groupName[] = "DaphneGroup";
        if (TDMS_AddGroupToFile(&Group, &FileTDMS, groupName) != TDMS_OK) {
            fclose(MyFile);
            throw std::runtime_error("WriteTdms: Add group failed!");
        }

        size_t numRows = arg->getNumRows();
        size_t numCols = arg->getNumCols();

        // Step 3: Add channels for each column (as each column can represent a distinct data stream)
        for (size_t j = 0; j < numCols; ++j) {
            std::string channelNameStr = "Channel_" + std::to_string(j + 1);
            char* channelName = new char[channelNameStr.length() + 1];  
            std::strcpy(channelName, channelNameStr.c_str());  


            TDMS_Channel_t Channel;

            // Use double data type for this example
            if (TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_DoubleFloat) != TDMS_OK) {
                 delete[] channelName;
                fclose(MyFile);
                throw std::runtime_error("WriteTdms: Add channel failed!");
            }

            // Step 4: Extract the column data for this channel
            std::vector<double> columnData(numRows);
            for (size_t i = 0; i < numRows; ++i) {
                columnData[i] = static_cast<double>(arg->get(i, j)); // Get value from the matrix
            }

            // Step 5: Write the column data to the TDMS file
            uint32_t size = 0;
            TDMS_SetChannelDataValues(&Channel, NULL, &size, columnData.data(), numRows);
            uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
            if (!buffer) {
                fclose(MyFile);
                throw std::runtime_error("WriteTdms: Memory allocation failed!");
            }

            TDMS_SetChannelDataValues(&Channel, buffer, &size, columnData.data(), numRows);
            fwrite(buffer, 1, size, MyFile);
            free(buffer);
        }

        // Step 6: Close the TDMS file
        fclose(MyFile);
    }
};

template <> struct WriteTdms<Frame> {
    static void apply(const Frame *arg, const char *filename) {
        // Step 1: Open the TDMS file for writing
        FILE *MyFile = fopen(filename, "wb");
        if (!MyFile) {
            throw std::runtime_error("WriteTdms: File open failed!");
        }

        TDMS_File_t FileTDMS;
        if (TDMS_InitFile(&FileTDMS) != TDMS_OK) {
            fclose(MyFile);
            throw std::runtime_error("WriteTdms: TDMS Init failed!");
        }

        // Step 2: Add a group to the TDMS file
        TDMS_Group_t Group;
        char groupName[] = "DaphneGroup";
        if (TDMS_AddGroupToFile(&Group, &FileTDMS, groupName) != TDMS_OK) {
            fclose(MyFile);
            throw std::runtime_error("WriteTdms: Add group failed!");
        }

        size_t numRows = arg->getNumRows();
        size_t numCols = arg->getNumCols();

        size_t i ;
        TDMS_Result_t j ;

        for ( i=0; i<numCols ; i++){
            std::string channelNameStr = "Channel_" + std::to_string(i + 1);
            char* channelName = new char[channelNameStr.length() + 1];  
            std::strcpy(channelName, channelNameStr.c_str());  
            TDMS_Channel_t Channel;
            const void* array = arg->getColumnRaw(i);
            ValueTypeCode vtc = arg->getColumnType(i);
            switch(vtc){
                case ValueTypeCode::SI8:{
                    j  = TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_I8);
                    if ( j != TDMS_OK) {
                        
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out si8!");
                        throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(int8_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (int8_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::SI32:{
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_I32);
                    if (j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out si32!");
                        throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(int32_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (int32_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::SI64:{
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_I64);
                    if (j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out si64!");
                        throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(int64_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (int64_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::UI8:{
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_U8);
                    if (j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out ui8!");
                        else throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(u_int8_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (u_int8_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::UI32:{
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_U32);
                    if ( j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out ui32!");
                        throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(u_int32_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (u_int32_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::UI64:{
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_U64);
                    if (j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out ui64!");
                        throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(u_int64_t*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (u_int64_t*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::F32:{
                    TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_SingleFloat);
                    if ( j != TDMS_OK) {
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out float!");
                        else throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(float*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (float*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                }
                case ValueTypeCode::F64:{
    
                    j=TDMS_AddChannelToGroup(&Channel, &Group, channelName, TDMS_DataType_DoubleFloat);
                    if (j != TDMS_OK) {                        
                        delete[] channelName;
                        fclose(MyFile);
                        if(j == TDMS_WRONG_ARG) throw std::runtime_error("WriteTdms: Add channel failed because of wrong arguement!");
                        else if( j ==TDMS_OUT_OF_CAP) throw std::runtime_error("WriteTdms: Add channel failed because of maxing out double!");
                        else throw std::runtime_error("WriteTdms: Add channel failed!");
                    }
                    uint32_t size = 0;
                    TDMS_SetChannelDataValues(&Channel, NULL, &size,(double*)array, numRows);
                    uint8_t *buffer = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
                    if (!buffer) {
                        fclose(MyFile);
                        throw std::runtime_error("WriteTdms: Memory allocation failed!");
                    }

                    TDMS_SetChannelDataValues(&Channel, buffer, &size, (double*)array, numRows);
                    fwrite(buffer, 1, size, MyFile);
                    free(buffer);
                    break;
                    }
                    
                }
            }
            fclose(MyFile);
        }
        

    };

#endif // SRC_RUNTIME_LOCAL_IO_WRITETDMS_H