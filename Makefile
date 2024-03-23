CC = gcc
CFLAGS = -g -Wall -Wshadow
frontEnd: frontEnd.o parser.o scanner.o
	$(CC) $(CFLAGS) -v frontEnd.o parser.o scanner.o -o frontEnd
frontEnd.o: frontEnd.c parser.h
	$(CC) $(CFLAGS) -c frontEnd.c parser.h
parser.o: parser.c parser.h scanner.h ttoken.h node.h
	$(CC) $(CFLAGS) -c parser.c parser.h scanner.h ttoken.h node.h
scanner.o: scanner.c scanner.h ttoken.h langscan.h
	$(CC) $(CFLAGS) -c scanner.c scanner.h ttoken.h langscan.h
.PHONY: clean
clean:
	rm *.o frontEnd *.gch
