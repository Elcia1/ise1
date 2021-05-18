CC=gcc
C++=g++
LD=g++
CFLAGS=-c -Wall -pedantic-errors -O3 -std=gnu11 -D_GNU_SOURCE -I../
LDFLAGS=
OBJECTS=007client.o ../exp1lib.o
EXECUTABLE=007client

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(C++) $(CFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f ${EXECUTABLE} ${EXECUTABLE}.exe ${OBJECTS} core

