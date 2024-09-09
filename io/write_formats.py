from nptdms import TdmsWriter, ChannelObject
import numpy

# Path to save the TDMS file
file_path = "./tdmsTests/uint8.tdms"

# Create a list of uint32 arrays for each channel
channels = []
for i in range(1, 11):  # Loop to create 10 channels
    # Generate an array of uint32 integers from 0 to 9
    data_array = numpy.arange(10, dtype=numpy.uint8)
    channel_name = f'channel{i}'
    channel = ChannelObject('group name', channel_name, data_array)
    channels.append(channel)

# Write to the TDMS file
with TdmsWriter(file_path) as tdms_writer:
    tdms_writer.write_segment(channels)
