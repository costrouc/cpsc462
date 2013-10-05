Author: Christopher Ostrouchov
Class: CPSC 462

=======
Description
=======
readNumbers is an executable that will read numbers from a given text file

Can be run as:
./readNumbers src1 numbers0001.txt computeEffort 0.5

Where numbers0001.txt has 1 integer with a '\n' at the end of the line

========
Compiling
========
Compiling instructions are detailed within the google doc provided for the asignment.

========
Statistics
========

Reading timing.txt:
	timing.txt is a file that contains usefull information about the runtime statistics of the program.
	The first column represents the name of the file being used by the program.
	The second column gives the real time required for the program to run with the given file. This
	program runs in O(N) * computeEffort. Where N is the number of numbers in the text file.
