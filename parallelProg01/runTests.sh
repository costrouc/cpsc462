#!/bin/bash
echo "Bash version: ${BASH_VERSION}"

# Remove old files for test
rm -f timing.txt numbers*.txt

# Create new number files
python generateNumFiles.py 9

# Run test on each file
for test in numbers*.txt
  do
    /usr/bin/time --format="$test %E" ./readNumbers src1 $test computeEffort 1.0 2>> timing.txt
  done