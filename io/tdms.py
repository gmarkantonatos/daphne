from nptdms import TdmsFile

tdms_file = TdmsFile.read("./tdmsTests/2channels.tdms")
group = tdms_file.groups()
print(tdms_file.groups())

#channels = group[0]["VaGroundV"]
channels = group[0]["channel1"]
print(group[0].channels())
first_channel_value = channels[1]
print(len(channels))
for i in range(0, len(channels)):
    print(channels[i])
# print(channels[:])

# group = tdms_file['group name']
# channel = group['channel name']
# channel_data = channel[:]
# channel_properties = channel.properties
