Author: Christopher Ostrouchov MS&E Graduate Research Assistant  
Please Contact costrouc at utk dot edu for questions.

This program assumes that it is operating on a cluster that is
operated with the sun grid engine queuing system. For ease of
operation please only use the makefile! A lot of things are
automated with shell scripting controlled by the makefile.
Including test dependencies.

Dependencies:
-  python 3.2.1
-  matplotlib
-  gcc
-  openmpi-gcc

Terminology:
-  __nodes__ a collection of cores
-  __core__ a single operation unit that shares the same registers
-  __process__ a single job for the OS to run

# Installation

To install the particle executable:
> make

# Tests

## Current Tests Available
Timing - Running code on c cores with p processes (limit of 8 cores).
In order the change these parameters look at script/timing.sh.
Change `$maxNumProcessors` and `$maxNumNodes`.

## Running Tests
To generate test run:
> make test

# Plots
The plots should be automatically generated once the tests are done. This is done via a dependency of plotting the timing data once sun grid engine tests being done. In the case that this does not work please run the following command once the tests are done. You can easily see if your jobs are done with `qstat -u <username>`.  

> make plots  

## Viewing Plots

Then `cd` to plots directory to view plots

# Running Program
The program can be run as:
> ./particle numParticles *numParticles* shape *shape* radius *radius*

*numParticles* - number of Particles to run in simulation
                 (0 < *numParticles* < MAX_UNSIGNED_INT)  
*shape*        - volume that random particles are placed into
                 (*shape* : {disk, square})  
*radius*       - radius of the shape for the particles to be placed into
                 (0.0 < *radius* < MAX_DOUBLE)  

# Capabilities

## Generate Statistics on particles

The program will calculate the mean and variance of all:
positions, distances, and inverse squared distance  

Assume in 2D we have 2 particles p,q.

/[distance = sqrt((p.x - q.x)^2 + (p.y - q.y)^2)\]

