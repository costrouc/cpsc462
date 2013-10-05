#!/usr/bin/python

import sys
import math
import random

"""
File to quickly generate text files with 2^0, 2^1, ..., 2^n numbers.
Each number is separated by a newline. n is specified as a command
line argument.
"""

def usage():
    print(sys.argv[0], 'numberOfFiles')

if (len(sys.argv) != 2):
    usage()

for i in range(int(sys.argv[1])):
    numNumbers = pow(2, i)
    print('Creating file numbers%04d.txt' % numNumbers)

    f = open('numbers%04d.txt' % numNumbers, "w")

    for i in range(numNumbers):
        f.write('%d\n' % random.randint(0,100))

    f.close()
    


