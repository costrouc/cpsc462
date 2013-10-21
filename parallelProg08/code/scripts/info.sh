#!/bin/bash

# This is a shell script to print job info from queued job
# It prints the import enviroment information, loaded modules
# Full enviroment, and pe_hostfile

# Print Import enviroment info
echo "================================================================"
echo SHELL=$SHELL
echo JOB_NAME=$JOB_NAME
echo JOB_ID=$JOB_ID
echo SGE_TASK_ID=$SGE_TASK_ID
echo SGE_TASK_FIRST=$SGE_TASK_FIRST
echo SGE_TASK_LAST=$SGE_TASK_LAST
echo NSLOTS=$NSLOTS
echo QUEUE=$QUEUE
echo SGE_CWD_PATH=$SGE_CWD_PATH
echo PATH=$PATH
echo SGE_STDIN_PATH=$SGE_STDIN_PATH
echo SGE_STDOUT_PATH=$SGE_STDOUT_PATH
echo SGE_STDERR_PATH=$SGE_STDERR_PATH
echo SGE_O_HOST=$SGE_O_HOST
echo SGE_O_PATH=$SGE_O_PATH
echo "================================================================"

# Print loaded modules
printf "\nLoaded Modules:\n"
module list

# List environment variables
printf "\nEnviroment for script\n"
env

# Prints the hosts that I requested!!!
printf "\nHostfile used in job run:\n"
cat $PE_HOSTFILE
cat $PE_HOSTFILE > MACHINES

# Print just the machine names
awk '{print $1}' $PE_HOSTFILE >> MACHINE_NAMES

