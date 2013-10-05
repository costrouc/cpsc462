CC=gcc
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=parseFlags.c \
	readNumbers.c \
	main.c \
	compute.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=readNumbers

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o parallelProg01.tgz timing.txt numbers*.txt

pristine: clean
	rm -f $(EXECUTABLE) *~

test: $(EXECUTABLE)
	sh runTests.sh

plot: test
	python plotTiming.py

release: pristine
	cd ..; tar cvfz parallelProg01.tgz parallelProg01; mv parallelProg01.tgz parallelProg01/