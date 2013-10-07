Author: Christopher Ostrouchov MS&E Graduate Research Assistant
Contact: costrouc@utk.edu

# Installation

To install the particle executable:
> make

# Running Tests
The code will run timing tests for p processes 1-32 on n nodes 1-6

To generate test run:
> make test

To run each test
> cd test
> cd (into directory to run generated test)
> sh particles.sge (note: this will only run on the clusters preconfigured)

# Generate Plots
> cd test
> python plotData.py

Then cd to plots directory to view plots

# Running Program
The program can be run as:
> ./particle numParticles *numParticles* shape *shape* radius *radius*

*numParticles* - number of Particles to run in simulation
                 (0 < *numParticles* < __MAX_UNSIGNED_INT__)
*shape*        - volume that random particles are placed into
                 (*shape* : {disk, square})
*radius*       - radius of the shape for the particles to be placed into
                 (0.0 < *radius* < __MAX_DOUBLE__)

# Capabilities

## Generate Statistics on particles

The program will calculate the mean and variace of all:
positions, distances, and inverse squared distance


