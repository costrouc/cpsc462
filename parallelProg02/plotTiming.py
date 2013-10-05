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
    numNumbers.append(int(tokens[1].strip(str.ascii_letters + '.')))
    times.append( (60 * float(tokens[3].split(":")[0])) + float(tokens[3].split(":")[1]))
    line = inputFile.readline()

inputFile.close()

plt.plot(numNumbers, times, 'ro-')
plt.xlabel('Number of Particles [#]')
plt.ylabel('Time [seconds]')
plt.title('Time to Calculate Statistics for n Particles')
plt.savefig('plots/timing.png')
