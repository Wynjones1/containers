CC=clang

all:list.h list.c llist.h llist.c
	$(CC) list.c -c -o list.o -Wall
	$(CC) llist.c -c -o llist.o -Wall

clean:
	rm *.o
