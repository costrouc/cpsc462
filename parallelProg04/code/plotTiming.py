"""
File for plotting data
"""

import matplotlib.pyplot as plt

filename = "timing.txt"

inputFile = open(filename, "r")

line = inputFile.readline()

numParticles = []
times = []

while line != '':
    tokens = line.split()
    numParticles.append(int(tokens[1]))
    times.append(float(tokens[7]))
    line = inputFile.readline()

inputFile.close()

plt.plot(numParticles, times, 'ro-')
plt.xlabel('Number of Particles [#]')
plt.ylabel('Time [seconds]')
plt.title('Time to Calculate Statistics for n Particles')
plt.savefig('plots/timing.png')
