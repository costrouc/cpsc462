"""
File for plotting data
"""

import matplotlib.pyplot as plt

filename = "timing.txt"

inputFile1 = open(filename, "r")
inputFile2 = open('../n2/'+filename, "r")


line = inputFile1.readline()

numProcesses1 = []
numProcesses2 = []
times1 = []
times2 = []

while line != '':
    tokens = line.split()
    numProcesses1.append(int(tokens[3]))
    runTimes = []
    for i in range(5,len(tokens),2):
        runTimes.append(float(tokens[i]))

    times1.append(max(runTimes))
    line = inputFile1.readline()

inputFile1.close()

line = inputFile2.readline()

while line != '':
    tokens = line.split()
    numProcesses2.append(int(tokens[3]))
    runTimes = []
    for i in range(5,len(tokens),2):
        runTimes.append(float(tokens[i]))

    times2.append(max(runTimes))
    line = inputFile2.readline()

inputFile2.close()


plt.plot(numProcesses1[1:-1], times1[1:-1], 'ro-')
plt.plot(numProcesses2[1:-1], times2[1:-1], 'ro-')
plt.xlabel('Number of Processes [#]')
plt.ylabel('Time [seconds]')
plt.title('Time for n Processes to complete on 1 and 2 cores')
plt.savefig('../../plots/timingscompared.png')
