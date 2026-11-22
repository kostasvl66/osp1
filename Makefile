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
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM).o -o lib/$(PROGRAM)
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM2).o -o lib/$(PROGRAM2)
	@$(CC) $(CFLAGS) src/$(LIB).o src/$(PROGRAM3).o -o lib/$(PROGRAM3)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	@rm -f src/*.o bld/*
