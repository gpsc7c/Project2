CC = gcc
CFLAGS = -g -Wall -Wshadow
frontEnd: frontEnd.o parser.o scanner.o
	$(CC) $(CFLAGS) -v frontEnd.o parser.o scanner.o -o frontEnd
frontEnd.o: frontEnd.c node.h
	$(CC) $(CFLAGS) -c frontEnd.c node.h
parser.o: parser.c parser.h scanner.h ttoken.h node.h tree.h
	$(CC) $(CFLAGS) -c parser.c parser.h scanner.h ttoken.h node.h tree.h
scanner.o: scanner.c scanner.h ttoken.h langscan.h
	$(CC) $(CFLAGS) -c scanner.c scanner.h ttoken.h langscan.h
.PHONY: clean
clean:
	rm *.o frontEnd *.gch
