CC=gcc
C++=g++
LD=g++
CFLAGS=-c -Wall -pedantic-errors -O0 -g3 -std=gnu11 -D_GNU_SOURCE -I../
LDFLAGS=
OBJECTS=009server.o ../exp1lib.o
EXECUTABLE=009server

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(C++) $(CFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f ${EXECUTABLE} ${EXECUTABLE}.exe ${OBJECTS} core tmp.txt

