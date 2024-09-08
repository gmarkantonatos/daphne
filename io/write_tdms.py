from nptdms import TdmsWriter, ChannelObject
import numpy

with TdmsWriter("./tdmsTests/2channels.tdms") as tdms_writer:
    data_array = numpy.linspace(0, 1, 10)
    channel = ChannelObject('group name', 'channel1', data_array)
    tdms_writer.write_segment([channel])
    channel = ChannelObject('group name', 'channel2', data_array)
    tdms_writer.write_segment([channel])