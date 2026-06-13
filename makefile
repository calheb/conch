PROGRAM = conch
CC      = gcc
CFLAGS  = -g -std=c89 -pedantic -Wall -Wextra

all: $(PROGRAM)

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

$(PROGRAM): src/main.o
	$(CC) $(CFLAGS) -o $(PROGRAM) src/main.o

clean:
	rm -f src/*.o $(PROGRAM)
