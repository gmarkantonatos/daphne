from nptdms import TdmsFile

tdms_file = TdmsFile.read("tdmsTests/write1channel.tdms")
group = tdms_file.groups()
print(tdms_file.groups())

#channels = group[0]["VaGroundV"]
channels = group[0]["Channel_1"]
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
