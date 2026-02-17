CC = gcc
CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined

SRCS = memgrind.c mymalloc.c memtest.c
OBJS = memgrind.o mymalloc.o memtest.o
HDRS = mymalloc.h


memgrind: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) memgrind

