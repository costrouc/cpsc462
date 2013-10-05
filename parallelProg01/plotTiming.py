"""
File for plotting data
"""

import matplotlib.pyplot as plt
import string as str

filename = "timing.txt"

inputFile = open(filename, "r")

line = inputFile.readline()

numNumbers = []
times = []

while line != '':
    tokens = line.split()
    numNumbers.append(int(tokens[0].strip(str.ascii_letters + '.')))
    times.append( (60 * float(tokens[1].split(":")[0])) + float(tokens[1].split(":")[1]))
    line = inputFile.readline()

inputFile.close()

plt.plot(numNumbers, times, 'ro-')
plt.xlabel('Numbers read in [#]')
plt.ylabel('Time [seconds]')
plt.title('Time to Read in N numbers')
plt.savefig('plots/timing.png')
