CC = gcc
CFLAGS = -Wall -O2
LIB = msglib

PROGRAM = start
PROGRAM2 = proc
PROGRAM3 = enc

all: src/$(PROGRAM).c src/$(PROGRAM2).c src/$(PROGRAM3).c src/$(LIB).c
	@$(CC) $(CFLAGS) -c src/$(LIB).c -o src/$(LIB).o
	@$(CC) $(CFLAGS) -c src/$(PROGRAM).c -o src/$(PROGRAM).o
	@$(CC) $(CFLAGS) -c src/$(PROGRAM2).c -o src/$(PROGRAM2).o
	@$(CC) $(CFLAGS) -c src/$(PROGRAM3).c -o src/$(PROGRAM3).o
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM).o -o bld/$(PROGRAM)
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM2).o -o bld/$(PROGRAM2)
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM3).o -o bld/$(PROGRAM3)

run: $(PROGRAM)
	./$(PROGRAM)

test: 
	make all
	./bld/start
	./bld/proc 1
	./bld/enc 1

clean:
	@rm -f src/*.o bld/*
