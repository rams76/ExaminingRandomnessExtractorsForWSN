# The code is received as part of lab assignment
# Filename and port to modified prior to capture the data
# Ram Singh

import serial

ser = serial.Serial('COM7',9600)

f = open('RES1.txt','a')

while 1 :
    #s = ser.readline()
    #print(s)
    #f.write(s)
    f.write(ser.readline())
    f.close()
    f = open('RES1.txt','a')
    
    
