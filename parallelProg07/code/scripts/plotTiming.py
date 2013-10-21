import copy
from collections import namedtuple

TimingData = namedtuple("TimingData", "numNodes numProcesses times")

inputFile = open("timing.txt", "r")

line = inputFile.readline()

timeData = []

while line != "":
    tokens = line.split()
    numNodes = int(tokens[1])
    numProcesses = int(tokens[3])

    times = []
    for i in range(5, len(tokens), 2):
        times.append(float(tokens[i]))

    timeData.append(TimingData(numNodes, numProcesses, copy.deepcopy(times)))
    line = inputFile.readline()

inputFile.close()

import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt

import numpy as np

maxNumNodes = 8
maxNumProcesses = 32

fig = plt.figure(figsize=(10,20))
for i in range(1, maxNumNodes+1):
    plt.subplot(4,2,i)
    x = []
    y = []
    for t in timeData:
        if (t.numNodes == i):
            for j in range(len(t.times)):
                x.append(t.numProcesses)
                y.append(t.times[j])

    z = np.polyfit(x,y,1)
    p = np.poly1d(z)
    plt.text( 1, 700, 't = %2.2f + %2.2fn' % (z[1], z[0]))
    plt.plot(x, p(x), 'k--')    
    plt.axis([0,33, 0, 770])
    plt.scatter(x, y, color=np.random.rand(3,1), alpha=0.8)
    plt.xlabel('Number of Processes [#]')
    plt.ylabel('Time for Process [seconds]')
    plt.title('%d cores' % i) 

fig.savefig('../plots/timing_scatter.png' , transparent=True)

fig = plt.figure(figsize=(10,20))
for i in range(1, maxNumNodes+1):
    plt.subplot(4,2,i)
    x = np.array([t.numProcesses for t in timeData if t.numNodes == i])
    y = np.array([max(t.times) for t in timeData if t.numNodes == i])

    z = np.polyfit(x,y,1)
    p = np.poly1d(z)
    plt.text( 1, 700, 't = %2.2f + %2.2fn' % (z[1], z[0]))
    plt.axis([0,33, 0, 770])
    plt.plot(x, p(x), 'k--')    
    plt.scatter(x, y, color=np.random.rand(3,1))
    plt.xlabel('Number of Processes [#]')
    plt.ylabel('Time [seconds]')
    plt.title('%d cores' % i) 

fig.savefig('../plots/timing_max.png' , transparent=True)

fig = plt.figure(figsize=(15,10))
for i in range(1, maxNumNodes+1):
    x = np.array([t.numProcesses for t in timeData if t.numNodes == i])
    y = np.array([max(t.times) for t in timeData if t.numNodes == i])
    
    plt.plot(x, y, '-o', label='%d nodes' % i)

plt.axis([0, 33, 0, 770])
plt.xlabel('Number of Processes [#]')
plt.ylabel('Time [seconds]')
plt.title('Comparison of runtimes of n Processes on 1 .. 8 cores')
plt.legend()

fig.savefig('../plots/timing_compare.png' , transparent=True)


