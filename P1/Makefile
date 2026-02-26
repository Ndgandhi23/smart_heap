CC = gcc

CFLAGS = -g -std=c99 -Wall

ifeq ($(SAN),1)
CFLAGS += -fsanitize=address,undefined
endif

HDRS = mymalloc.h list.h tree.h

MEMGRIND_OBJS   = memgrind.o mymalloc.o list.o tree.o
MEMTEST_OBJS    = memtest.o  mymalloc.o list.o tree.o
CORRECT_OBJS    = coalescing_and_leak_testing.o mymalloc.o 
FREE1_OBJS      = free_test_1.o mymalloc.o
FREE2_OBJS      = free_test_2.o mymalloc.o
FREE3_OBJS      = free_test_3.o mymalloc.o

all: memgrind memtest coalescing_and_leak_testing free_test_1 free_test_2 free_test_3

memgrind: $(MEMGRIND_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

memtest: $(MEMTEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

coalescing_and_leak_testing: $(CORRECT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

free_test_1: $(FREE1_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

free_test_2: $(FREE2_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

free_test_3: $(FREE3_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o memgrind memtest coalescing_and_leak_testing free_test_1 free_test_2 free_test_3