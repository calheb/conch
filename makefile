PROGRAM = conch
CC      = gcc
CFLAGS  = -g -std=c89 -pedantic -Wall -Wextra

all: $(PROGRAM)

src/main.o: src/main.c src/history.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/history.o: src/history.c src/history.h
	$(CC) $(CFLAGS) -c src/history.c -o src/history.o

$(PROGRAM): src/main.o src/history.o
	$(CC) $(CFLAGS) -o $(PROGRAM) src/main.o src/history.o

clean:
	rm -f src/*.o $(PROGRAM)
