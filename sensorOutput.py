file = open("data.txt")
data = file.read

ALSData = []

i = 0
while i < 48:
    value = file.read(8)
    #value = "0x"+value
    _4b = (value[0]+value[1])
    _3b = (value[2]+value[3])
    _2b = (value[4]+value[5])
    _1b = (value[6]+value[7])
    rvalue = '0x' + _1b + _2b + _3b + _4b
    #print(rvalue)
    value = int(rvalue, 16)
    print(float(value)/100.0)
    ALSData.append(value)
    i = i + 1

#print(data)
#print(ALSData)
file.close()
