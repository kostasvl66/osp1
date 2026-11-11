CC = gcc
CFLAGS = -Wall -O2
ARGS = 

PROGRAM = start

$(PROGRAM): $(PROGRAM).c
	@$(CC) $(CFLAGS) $< -o $@

run: $(PROGRAM)
	./$(PROGRAM) $(ARGS)

clean:
	@rm -f *.o $(PROGRAM)
