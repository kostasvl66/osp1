CC = gcc
CFLAGS = -Wall -O2
ARGS = 

PROGRAM = start
PROGRAM2 = proc

$(PROGRAM): $(PROGRAM).c
	@$(CC) $(CFLAGS) $< -o $@
	@$(CC) $(CFLAGS) $(PROGRAM2).c -o $(PROGRAM2)

run: $(PROGRAM)
	./$(PROGRAM) $(ARGS)

clean:
	@rm -f *.o $(PROGRAM)
