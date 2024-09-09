from nptdms import TdmsWriter, ChannelObject
import numpy

# Path to save the TDMS file
file_path = "./tdmsTests/10channels.tdms"

# Create the data array
data_array = numpy.linspace(0, 1, 10)

# Create a list of channels
channels = []
for i in range(1, 11):  # Loop to create 10 channels
    channel_name = f'channel{i}'
    channel = ChannelObject('group name', channel_name, data_array)
    channels.append(channel)

# Write to the TDMS file
with TdmsWriter(file_path) as tdms_writer:
    tdms_writer.write_segment(channels)
