from nptdms import TdmsWriter, ChannelObject
import numpy

# Path to save the TDMS file
file_path = "./tdmsTests/10groups10channels.tdms"

# Create the data array
data_array = numpy.linspace(0, 1, 10)

# Create a list of channels
channels = []
for j in range(1,11):
    for i in range(1, 11):  # Loop to create 10 channels
        channel_name = f'channel{i}'
        channel = ChannelObject(f'group{j}', channel_name, data_array)
        channels.append(channel)

# Write to the TDMS file
with TdmsWriter(file_path) as tdms_writer:
    tdms_writer.write_segment(channels)


