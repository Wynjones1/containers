CC=clang
INCLUDE := -I./include
all:list.c llist.c
	$(CC) list.c -c -o list.o -Wall $(INCLUDE)
	$(CC) llist.c -c -o llist.o -Wall $(INCLUDE)

clean:
	rm *.o
