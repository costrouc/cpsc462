#!/bin/bash

# This script assumes that it is being run in the test dir
# current path should be */code/test/

numParticles="8000"
shape="square"
radius="1.0"

maxNumNodes="8"
maxNumProcesses="32"

testDirPath=$PWD

for numNodes in $(seq $maxNumNodes)
do
    testName="n$numNodes"
    
    # Create directory for tests
    # If directory exists remove it
    if [ -d $testName ]
    then
	echo "Removing old test $testName directory"
	rm -r $testName
    fi

    echo "Created test $testName: 1 .. $maxNumProcesses processes on $numNodes nodes"
    mkdir $testName
    cd $testName
    
    # Create Info on test run in directory
    printf "Ran executable particle with same parameters differing number of processors and nodes dedicated to the task see particle.qsub for complete details\n" >> testInfo.txt
    printf "Computing Info:\n" >> testInfo.txt
    printf "numNodes $numNodes\n" >> testInfo.txt
    printf "numProcesses 1 .. $maxNumProcesses\n\n" >> testInfo.txt

    printf "Parameters:\nnumParticles $numParticles\nshape $shape\nradius $radius\n" >> testInfo.txt
    
    # Create qsub sge submission file
    cp ../../scripts/timing.sge particles.sge

    sed -i "s/_job_name_/$testName/g" particles.sge
    sed -i "s/_num_nodes_/$numNodes/g" particles.sge
    sed -i "s/_max_num_processes_/$maxNumProcesses/g" particles.sge
    sed -i "s/_num_particles_/$numParticles/g" particles.sge
    sed -i "s/_shape_/$shape/g" particles.sge
    sed -i "s/_radius_/$radius/g" particles.sge

    # Submit job to queue
    qsub particles.sge
    
    # Return to original directory
    cd $testDirPath
done

# Submit ploting of tests
# This job is dependent on all the others
testNames=$(printf 'n%d,'  $(seq 1 $maxNumNodes))
cp ../scripts/plotTiming.sge .

# Job name requirements
# An object name is a sequence of up to 512 ASCII string char-
#     acters  except  "\n",  "\t",  "\r", " ", "/", ":", "'", "\",
#     "[", "]", "{", "}", "|", "(", ")", "@", "%", ","  or  the  "
#     character itself.

sed -i "s/_job_name_/plotTimings_n1-n$maxNumNodes/g" plotTiming.sge
sed -i "s/_test_names_/$testNames/g" plotTiming.sge

qsub plotTiming.sge

