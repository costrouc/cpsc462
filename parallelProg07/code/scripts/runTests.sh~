#!/bin/bash

# remove old timing.txt file
rm -f timing.txt

# Create mpiscript
rm -f particle.qsub



# Check if executables are made
if [ ! -d "./particles" ]
then
    make all
fi

if [ ! -d "./mytime" ]
then
    make mytime
fi

# Create Directory for test
# If it already exists remove it and recreate it
if [ ! -d "test/" ]
then
    echo "Creating test directory"
    mkdir test/
fi
cd test/

# Run timing tests
sh ../scripts/timing.sh