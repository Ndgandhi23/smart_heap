#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

#define MEMLENGTH 4096

static int heap_init = 0;


// already declares the heap globally but requires initializing 
    // aka setting the bytes equal to free bc right now they hold random info
static union { 
    char bytes[MEMLENGTH];
    double not_used;
} heap;

void * mymalloc (size_t size, char *file, int line){
    if(heap_init == 0){
        heap_init = 1;
        initilize_heap();
    }

    /*code to malloc() goes here*/

    // find the first free spot in heap via a loop 
        // this loop will only check the header to see if the space is free (headers stored in their own list?)
            // if its free, clear those many bytes and change the header
            // if the space isnt free, jump by the size of the payload 

    // NOTE: round size up to multiple of 8
    // NOTE: we can combine two freed chunks into one big one for malloc
        // aka combine 
    // NOTE: create bit patterns in headers for size and free/not free

    // returns a pointer to the payload NOT header 
    // OR returns null with additional print statement in this format:
        // malloc: Unable to allocate 1234 bytes (source.c:1000)

    int roundedSize = (size + 7) & ~7;
    
    for(int i=0; i<heap.bytes.length; i++){
        
    }
    
}

void myfree (void *ptr, char *file, int line){
    if(heap_init == 0){
        heap_init = 1; 
        initilize_heap();
    }

    // myfree should merge adjacent free chunks together so we dont need to worry about
        // that in mymalloc
}

// initializes the heap to 0 or whatever is equal to a free space
void initilize_heap(){
    
    // treat as one large chunk at first and edit as you go
    // have one big header to start which accounts for all the space
        // when mymalloc is first called:
            // edits header to be smaller to match memory required
            // creates a new header trailing the chunk to account for the rest of the free memory
}
