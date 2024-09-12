from nptdms import TdmsWriter, ChannelObject
import numpy
import random

# Path to save the TDMS file
file_path1= "./1channelsMatrixDouble.tdms"
file_path2= "./1channelsMatrixInt.tdms"
file_path3= "./10channelsMatrixDouble.tdms"
file_path4= "./10channelsMatrixInt.tdms"

# Create the data arrays
data_array1=[]
data_array2=[]
data_array3=[]
data_array4=[]
for i in range(0,10):
    data_array1.append(random.uniform(0,2))
    data_array2.append(random.randint(0,10))

# Create lists of channels
channels1 = []
channels2 = []
channels3 = []
channels4 = []

#create channels
channel_name="channel_1"
channel = ChannelObject('group name1', channel_name, data_array1)
channels1.append(channel)
channel = ChannelObject('group name1', channel_name, data_array2)
channels2.append(channel)

for i in range(1, 6):  # Loop to create 10 channels
    data_array3=[]
    data_array4=[]
    for j in range(0,10):
        data_array3.append(random.uniform(0,2))
        data_array4.append(random.randint(0,10))
    channel_name = f'channel{i}'
    channel = ChannelObject('group name1', channel_name, data_array3)
    channels3.append(channel)
    channel = ChannelObject('group name1', channel_name, data_array4)
    channels4.append(channel)
for i in range(6, 11):  # Loop to create 10 channels
    data_array3=[]
    data_array4=[]
    for j in range(0,10):
        data_array3.append(random.uniform(0,2))
        data_array4.append(random.randint(0,10))
    channel_name = f'channel{i}'
    channel = ChannelObject('group name2', channel_name, data_array3)
    channels3.append(channel)
    channel = ChannelObject('group name2', channel_name, data_array4)
    channels4.append(channel)

# Write to the TDMS file
with TdmsWriter(file_path1) as tdms_writer:
    tdms_writer.write_segment(channels1)
with TdmsWriter(file_path2) as tdms_writer:
    tdms_writer.write_segment(channels2)
with TdmsWriter(file_path3) as tdms_writer:
    tdms_writer.write_segment(channels3)
with TdmsWriter(file_path4) as tdms_writer:
    tdms_writer.write_segment(channels4)

#write files meta data
coma=","
squigl="{"
squigr="}"

f1=open(file_path1+'.meta', "w")
f1.write('{ "numRows":10,"numCols":1 ,"valueType" : "f64" }')
f1.close()
f2=open(file_path2+'.meta', "w")
f2.write('{ "numRows":10,"numCols":1 ,"valueType" : "si64" }')
f2.close()
f3=open(file_path3+'.meta', "w")
f3.write('{ "numRows":10,"numCols":10 ,"valueType" : "f64" }')
f3.close()
f4 =open(file_path4+'.meta', "w")
f4.write('{ "numRows":10,"numCols":10 ,"valueType" : "si64" }')
f4.close()