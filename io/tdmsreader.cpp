#include <iostream>
#include "libtdms.h"

int main() {
    // Replace "example.tdms" with your actual TDMS file path
    const char* fileName = "exampleMeasurements.tdms";
    
    // Open the TDMS file
    tdmsFile* file = tdms_open(fileName);
    if (!file) {
        std::cerr << "Failed to open TDMS file: " << fileName << std::endl;
        return 1;
    }

    // Iterate through the groups in the file
    tdmsGroup* group;
    while ((group = tdms_get_next_group(file)) != nullptr) {
        std::cout << "Group: " << group->name << std::endl;

        // Iterate through the channels in the group
        tdmsChannel* channel;
        while ((channel = tdms_get_next_channel(group)) != nullptr) {
            std::cout << "  Channel: " << channel->name << std::endl;
            std::cout << "  Data type: " << channel->dataType << std::endl;
            
            // Example: Read data if the channel is of type double
            if (channel->dataType == TDMS_DOUBLE) {
                double* data = static_cast<double*>(channel->data);
                for (size_t i = 0; i < channel->nValues; ++i) {
                    std::cout << "    Data[" << i << "]: " << data[i] << std::endl;
                }
            }
        }
    }

    // Close the TDMS file
    tdms_close(file);
    return 0;
}
