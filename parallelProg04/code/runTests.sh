#! /usr/bin/bash

# remove old timing.txt file
rm -f timing.txt

for numParticles in 1000 2000 3000 4000 5000 6000 7000 8000
do
  echo -n "numParticles $numParticles " >> timing.txt 
  ./mytime ./particles numParticles $numParticles shape square radius 1.0 2>> timing.txt
done