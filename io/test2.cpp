#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>

// TOC Mask flags
const uint32_t kTocMetaData = 0x02;
const uint32_t kTocRawData = 0x04;
const uint32_t kTocNewObjectList = 0x08;
const uint32_t kTocInterleavedData = 0x20;
const uint32_t kTocBigEndian = 0x80;
const uint32_t kTocDAQmxRawData = 0x1000;

// Structure to manage TDMS file information
struct TdmsFile {
    std::ifstream file; // Input file stream for binary reading
    std::string filename;
};

// Structure to hold metadata for each object (group/channel)
struct ObjectMetadata {
    std::string path;
    std::unordered_map<std::string, std::string> properties;
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

// Function to read and parse the lead-in of a TDMS file segment
bool readLeadIn(TdmsFile &tdms, uint32_t &tocMask, uint64_t &dataOffset) {
    // A TDMS lead-in is 28 bytes
    char leadIn[28];

    // Read the lead-in from the file
    if (!tdms.file.read(leadIn, 28)) {
        std::cerr << "Failed to read lead-in" << std::endl;
        return false;
    }

    // Extract and verify the Tag (first 4 bytes)
    char tag[5] = {0};
    std::memcpy(tag, leadIn, 4);
    if (std::strcmp(tag, "TDSm") != 0) {
        std::cerr << "Invalid TDMS segment tag: " << tag << std::endl;
        return false;
    }
    std::cout << "TDMS Segment Tag: " << tag << std::endl;

    // Extract the TOC Mask (next 4 bytes)
    std::memcpy(&tocMask, leadIn + 4, 4);
    std::cout << "TOC Mask: 0x" << std::hex << tocMask << std::dec << std::endl;

    // Extract the Version Number (next 4 bytes)
    uint32_t versionNumber;
    std::memcpy(&versionNumber, leadIn + 8, 4);
    std::cout << "Version Number: " << versionNumber << std::endl;

    // Extract the Segment Length (next 8 bytes)
    uint64_t segmentLength;
    std::memcpy(&segmentLength, leadIn + 12, 8);
    std::cout << "Segment Length: " << segmentLength << " bytes" << std::endl;

    // Extract the Data Offset (next 8 bytes)
    std::memcpy(&dataOffset, leadIn + 20, 8);
    std::cout << "Data Offset: " << dataOffset << " bytes" << std::endl;

    return true;
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

    TdmsFile tdms;
    if (!openTdmsFile(tdms, argv[1])) {
        return 1;
    }

    uint32_t tocMask;
    uint64_t dataOffset;

    if (!readLeadIn(tdms, tocMask, dataOffset)) {
        closeTdmsFile(tdms);
        return 1;
    }

    if (tocMask & kTocMetaData) {
        std::vector<ObjectMetadata> objects;
        if (!readMetadata(tdms, dataOffset, objects)) {
            closeTdmsFile(tdms);
            return 1;
        }
    } else {
        std::cout << "No metadata in this segment." << std::endl;
    }

    closeTdmsFile(tdms);
    return 0;
}
