from nptdms import TdmsWriter, ChannelObject
import numpy

with TdmsWriter("test.tdms") as tdms_writer:
    data_array = numpy.linspace(0, 1, 10)
    channel = ChannelObject('group name', 'channel name', data_array)
    tdms_writer.write_segment([channel])