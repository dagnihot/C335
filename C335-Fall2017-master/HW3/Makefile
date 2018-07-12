CC = gcc
CFLAGS = -g

test: hw3.o
	$(CC) $(LDFLAGS) -o test hw3.o

hw3.o: hw3.c
	$(CC) $(CFLAGS) -c hw3.c

clean:
	@rm *.o
