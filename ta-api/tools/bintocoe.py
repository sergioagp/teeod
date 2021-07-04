#!/usr/bin/python

import sys
import os
import struct

def tohex(c):
    return format(c, '02x')


filebin = open(sys.argv[1], "rb")

filecoe = open(os.path.splitext(sys.argv[1])[0] + ".coe", "w")

filecoe.write("memory_initialization_radix=16;\n")
filecoe.write("memory_initialization_vector=\n")

data = filebin.read()

# for byte in data[0:-1]:
#     filecoe.write(format(ord(byte), '02x') + ',\n')

# filecoe.write(format(ord(data[-1]), '02x')  + '\n')


for i in range(0,len(data)-4,4):
    filecoe.write(tohex(data[i+3]) + tohex(data[i+2]) + tohex(data[i+1]) + tohex(data[i]) + ',\n')

filecoe.write( tohex(data[-1])+tohex(data[-2])+  tohex(data[-3])+  tohex(data[-4]) + '\n')

filecoe.close()
filebin.close()
