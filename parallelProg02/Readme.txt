Author: Christopher Ostrouchov MS&E Graduate Research Assistant
Contact: costrouc@utk.edu

# Installation

To install the particle executable:
> make

# Running Tests

To run test run either:
> sh runTests.sh
> make test

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


