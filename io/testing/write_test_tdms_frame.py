from nptdms import TdmsWriter, ChannelObject
import numpy
import random

file_path2="10channelsFrameSingle.tdms"
file_path1="10channelsFrameMixed.tdms"

data_array11=[]
data_array12=[]
data_array2=[]


channels1 = []
channels2 = []

for i in range(0,5):
    data_array11=[]
    data_array12=[]
    data_array2=[]
    for j in range(0,10):
        data_array11.append(random.uniform(0,2))
        data_array12.append(random.randint(0,10))
        data_array2.append(random.randint(0,10))

    channel_name1 = f'channel{2*i}'
    channel_name2 = f'channel{2*i+1}'
    channel = ChannelObject('group name1', channel_name1, data_array11)
    channels1.append(channel)
    channel = ChannelObject('group name1', channel_name2, data_array12)
    channels1.append(channel)
    channel = ChannelObject('group name1', channel_name1, data_array2)
    channels2.append(channel)
    channel = ChannelObject('group name1', channel_name2, data_array2)
    channels2.append(channel)

with TdmsWriter(file_path1) as tdms_writer:
    tdms_writer.write_segment(channels1)
with TdmsWriter(file_path2) as tdms_writer:
    tdms_writer.write_segment(channels2)

schema1=''
schema2=''

for i in range(0,4) : 
    schema1+='{ "label" : "'+ str(2*i)+  '" , "valueType": "f64"  },'
    schema1+='{ "label" : "'+ str(i*2+1)+  '" , "valueType": "si64"  },'
    schema2+='{ "label" : "'+ str(i*2)+  '" , "valueType": "si64"  },'
    schema2+='{ "label" : "'+ str(i*2+1)+  '" , "valueType": "si64"  },'
schema1+='{ "label" : "8" , "valueType": "f64"  },'
schema1+='{ "label" : "9" , "valueType": "si64"  }'
schema2+='{ "label" : "8" , "valueType": "si64"  },'
schema2+='{ "label" : "9" , "valueType": "si64"  }'
f1=open(file_path1+'.meta', "w")
f1.write('{ "numRows":10,"numCols":10 ,"schema" : [ '+schema1+ ' ]}')
f1.close()
f2=open(file_path2+'.meta', "w")
f2.write('{ "numRows":10,"numCols":10 ,"schema" : [ '+schema2+ ' ]}')
f2.close()