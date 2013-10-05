CC=gcc
CFLAGS=-g -c -Wall
LIB=-lm
LDFLAGS=
SOURCES=parseFlags.c \
	main.c \
	particle.c \
	statistics.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=particles

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIB) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o parallelProg02.tgz timing.txt

pristine: clean
	rm -f $(EXECUTABLE) *~

test: $(EXECUTABLE)
	sh runTests.sh

plot: test
	python plotTiming.py

release: pristine
	cd ..; tar cvfz parallelProg02.tgz parallelProg02; mv parallelProg02.tgz parallelProg02/