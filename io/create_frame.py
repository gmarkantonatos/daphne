from nptdms import TdmsWriter, ChannelObject
import numpy as np

file_path1 = "readTdmsFrame1.tdms"
file_path2 = "readTdmsFrame2.tdms"

channels1 = []
channels2 = []

# Fixed data for reproducibility
fixed_data11 = np.linspace(0, 2, 10)  # Linearly spaced numbers between 0 and 2
fixed_data12 = np.arange(10)  # Integers from 0 to 9
fixed_data2 = np.arange(10, 20)  # Integers from 10 to 19

for i in range(5):
    channel_name1 = f'channel{2*i}'
    channel_name2 = f'channel{2*i+1}'
    
    channel = ChannelObject('group name1', channel_name1, fixed_data11)
    channels1.append(channel)
    channel = ChannelObject('group name1', channel_name2, fixed_data12)
    channels1.append(channel)
    
    channel = ChannelObject('group name1', channel_name1, fixed_data2)
    channels2.append(channel)
    channel = ChannelObject('group name1', channel_name2, fixed_data2)
    channels2.append(channel)

with TdmsWriter(file_path1) as tdms_writer:
    tdms_writer.write_segment(channels1)
with TdmsWriter(file_path2) as tdms_writer:
    tdms_writer.write_segment(channels2)

# Metadata
schema1 = ''
schema2 = ''
for i in range(4):
    schema1 += f'{{ "label" : "{2*i}", "valueType": "f64" }},'
    schema1 += f'{{ "label" : "{2*i+1}", "valueType": "si64" }},'
    schema2 += f'{{ "label" : "{2*i}", "valueType": "si64" }},'
    schema2 += f'{{ "label" : "{2*i+1}", "valueType": "si64" }},'
schema1 += '{ "label" : "8", "valueType": "f64" },'
schema1 += '{ "label" : "9", "valueType": "si64" }'
schema2 += '{ "label" : "8", "valueType": "si64" },'
schema2 += '{ "label" : "9", "valueType": "si64" }'

with open(file_path1 + '.meta', "w") as f1:
    f1.write(f'{{ "numRows":10,"numCols":10,"schema" : [ {schema1} ]}}')
with open(file_path2 + '.meta', "w") as f2:
    f2.write(f'{{ "numRows":10,"numCols":10,"schema" : [ {schema2} ]}}')
