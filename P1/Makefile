CC = gcc

# Base flags (safe everywhere)
CFLAGS = -g -std=c99 -Wall

# Sanitizers (enabled only if SAN=1 is passed)
ifeq ($(SAN),1)
CFLAGS += -fsanitize=address,undefined
endif

HDRS = mymalloc.h list.h tree.h

MEMGRIND_OBJS   = memgrind.o mymalloc.o list.o tree.o
MEMTEST_OBJS    = memtest.o  mymalloc.o list.o tree.o
CORRECT_OBJS    = correctness_testing.o mymalloc.o list.o tree.o

all: memgrind memtest correctness_testing

memgrind: $(MEMGRIND_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

memtest: $(MEMTEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

correctness_testing: $(CORRECT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o memgrind memtest correctness_testing