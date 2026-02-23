CC = gcc
CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined

HDRS = mymalloc.h list.h tree.h

MEMGRIND_OBJS = memgrind.o mymalloc.o list.o tree.o
MEMTEST_OBJS  = memtest.o  mymalloc.o list.o tree.o

all: memgrind memtest

memgrind: $(MEMGRIND_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

memtest: $(MEMTEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o memgrind memtest