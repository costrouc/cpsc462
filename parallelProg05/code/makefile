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

mytime: mytime.c
	$(CC) mytime.c -o mytime

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o parallelProg02.tgz timing.txt

pristine: clean
	rm -f $(EXECUTABLE) mytime *~

test: $(EXECUTABLE) mytime
	sh scripts/runTests.sh

plot: test
	python plotTiming.py

release: pristine
	cd ..; tar --exclude='code/test' -zcvf parallelProg05.tgz code; mv parallelProg05.tgz code/.