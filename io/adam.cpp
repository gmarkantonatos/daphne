#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>

// TOC Mask flags

#define kTocMetaData         (1L<<1)
#define kTocRawData          (1L<<3)
#define kTocDAQmxRawData     (1L<<7)
#define kTocInterleavedData  (1L<<5)
#define kTocBigEndian        (1L<<6)
#define kTocNewObjList       (1L<<2)

struct LeadIn {
    char tag[4];
    uint32_t ToCmask;
    uint32_t verionNum;
    uint64_t nextsegoff;
    uint64_t rawdataoff;
};

// Structure to manage TDMS file information
struct TdmsFile {
    std::ifstream file; // Input file stream for binary reading
    std::string filename;
};

// Structure to hold metadata for each object (group/channel)
struct ObjectMetadata {
    uint32_t numOfObj;
    std::string path;
    std::unordered_map<std::string, std::string> properties;
    uint32_t remainingObj;
};

// Function to open a TDMS file
bool openTdmsFile(TdmsFile &tdms, const std::string &filename) {
    tdms.file.open(filename, std::ios::binary);
    if (!tdms.file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    tdms.filename = filename;
    return true;
}

// Function to close the TDMS file
void closeTdmsFile(TdmsFile &tdms) {
    if (tdms.file.is_open()) {
        tdms.file.close();
    }
}

// Function to read the metadata section
bool readMetadata(TdmsFile &tdms, uint64_t dataOffset, std::vector<ObjectMetadata> &objects) {
    // Calculate the metadata size
    uint64_t metadataSize = dataOffset - 28; // 28 bytes for the lead-in

    if (metadataSize <= 0) {
        std::cerr << "No metadata present or incorrect data offset." << std::endl;
        return false;
    }

    // Read the metadata section into a buffer
    std::vector<char> metadataBuffer(metadataSize);
    if (!tdms.file.read(metadataBuffer.data(), metadataSize)) {
        std::cerr << "Failed to read metadata section" << std::endl;
        return false;
    }

    // Parse the metadata buffer (simplified for now)
    size_t offset = 0;
    while (offset < metadataSize) {
        // Read the length of the object path (4 bytes)
        uint32_t pathLength;
        std::memcpy(&pathLength, metadataBuffer.data() + offset, 4);
        offset += 4;

        // Read the object path
        std::string objectPath(metadataBuffer.data() + offset, pathLength);
        offset += pathLength;

        // Create and store the object metadata
        ObjectMetadata object;
        object.path = objectPath;
        objects.push_back(object);

        std::cout << "Object Path: " << objectPath << std::endl;

        // Here, you would continue to parse additional metadata, such as properties, etc.
    }

    return true;
}

// Main function to test the TDMS reader
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <tdms_file>" << std::endl;
        return 1;
    }

    LeadIn leadin; 
    ObjectMetadata metadata;
    //char * buf ;
    TdmsFile tdms;
    if (!openTdmsFile(tdms, argv[1])) {
        return 1;
    }

    uint32_t tocMask;
    uint64_t dataOffset;

    if(!tdms.file.read((char *)&leadin , 28)){
        std::cerr << " could not read leadin\n";
        return -1 ;
    }
    char tagg[5]={0};
    memcpy(tagg,leadin.tag,4);
    tagg[4]='\0';
    std::cout << "tdms tag is :" << leadin.tag << std::endl;
    std::cout << "tdms mask is : "<< leadin.ToCmask << std::endl;
    std::cout<< " tdms version number : " << leadin.verionNum << std::endl;

    if(!(leadin.ToCmask & kTocMetaData) == 0) {
        std::cout << "segment has meta data\n";
        if(!tdms.file.read((char *)&metadata , 4)){
            std::cerr << " could not read leadin\n";
        return -1 ;
        }
        std::cout << "segment has " << metadata.numOfObj << " objects in metadata section\n";
    }

    if((leadin.ToCmask & kTocRawData) == 0 ) std::cout << "no raw data in segment \n";
    else std::cout << "there are raw data in segment \n";
    // if (!readLeadIn(tdms, tocMask, dataOffset)) {
    //     closeTdmsFile(tdms);
    //     return 1;
    // }

    // if (tocMask & kTocMetaData) {
    //     std::vector<ObjectMetadata> objects;
    //     if (!readMetadata(tdms, dataOffset, objects)) {
    //         closeTdmsFile(tdms);
    //         return 1;
    //     }
    // } else {
    //     std::cout << "No metadata in this segment." << std::endl;
    // }

    closeTdmsFile(tdms);
    return 0;
}