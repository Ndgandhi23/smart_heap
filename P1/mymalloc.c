#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mymalloc.h"
#include <string.h>
#include <stdbool.h>

#define MEMLENGTH 4096

static int heap_init = 0;


static union { 
    char bytes[MEMLENGTH]; // 4096 indices aka bytes
    double not_used;
} heap; // heap.bytes

struct header{
    uint32_t size; // size of payload
    uint32_t freed; // 1 is freed AND 0 is not freed
};



static void my_little_leaky(void){
    struct header headerToCheck; // tracking header which jumps thorugh heap
    int chunk_counter = 0;
    int bytes_leaked = 0; 

    for(int i=0; i<=MEMLENGTH-8;){ 
        
        memcpy(&headerToCheck, (struct header*)(heap.bytes + i), sizeof(struct header));

        if(headerToCheck.freed == 0){
            chunk_counter++;
            bytes_leaked += headerToCheck.size;
        }

        i += (headerToCheck.size + sizeof(headerToCheck)); // i jumps to next header
    }

    if(chunk_counter > 0){
        fprintf(stderr, "mymalloc: %d bytes leaked in %d objects.\n", bytes_leaked, chunk_counter);
    }
}

static void initilize_heap(){
    
    memset(heap.bytes, '\0', MEMLENGTH);

    // creates the first header with the rest of the heap being its free chunk
    struct header firstHeader;
    firstHeader.freed = 1; 
    firstHeader.size = MEMLENGTH - sizeof(struct header);

    memcpy((struct header*)&heap.bytes, &firstHeader, sizeof(struct header));

    atexit(my_little_leaky);

}


void * mymalloc (size_t size, char *file, int line){
    if(heap_init == 0){
        heap_init = 1;
        initilize_heap();
    }

    int roundedSize = (size + 7) & ~7; //rounds size to a multiple of 8

    struct header headerToAllocate; // header we want to put into heap
    headerToAllocate.size = roundedSize;
    headerToAllocate.freed = 0;

    struct header headerToCheck; // tracking header which jumps thorugh heap
    void * result = NULL; // pointer we are returning

    for(int i=0; i<=MEMLENGTH-8;){ 
        
        memcpy(&headerToCheck, (struct header*)(heap.bytes + i), sizeof(struct header));

        if(headerToCheck.freed == 1 && headerToCheck.size >= headerToAllocate.size){
            
            struct header newHeader; // new header for next chunk
            newHeader.freed = 1;

            memcpy((struct header*)(heap.bytes + i), &headerToAllocate, sizeof(struct header)); // make headerToAllocate equal the headerToCheck pointer
            
            // if there is enough space for a header but not a payload, it creates a header of length 0
            if((headerToCheck.size - headerToAllocate.size >= 8)){ 
                newHeader.size = headerToCheck.size - headerToAllocate.size - sizeof(struct header);
                memcpy((struct header*)(heap.bytes + i + sizeof(struct header) + roundedSize), &newHeader, sizeof(struct header)); // put newHeader into heap.bytes
            }
            
            result = (void*)(heap.bytes + i + sizeof(struct header)); // pointer to the payload
            break;
        }

        i += (headerToCheck.size + sizeof(struct header)); // i jumps to next header
    }

    if (result == NULL){
        fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
    }   

    return result; 
}


bool ptrExists(void *ptr){
    if(ptr == NULL){
        return false;
    }
    struct header *tempPtr; // pointer to header inside the heap
    struct header headerToCheck; // tracking header which jumps thorugh heap

    for(int i=0; i<=MEMLENGTH-8;){ 
        
        tempPtr = (struct header*)(heap.bytes + i); 

        if(tempPtr == ptr-sizeof(struct header)){ // found the pointer
            return true;
        }

        memcpy(&headerToCheck, (struct header*)(heap.bytes + i), sizeof(struct header));
        i += (headerToCheck.size + sizeof(headerToCheck)); 
    }

    return false;
}

void myfree (void *ptr, char *file, int line){
    if(heap_init == 0){
        heap_init = 1; 
        initilize_heap();
    }

    if(!ptrExists(ptr)){ // checks to see if the pointer is correct and exists as a header
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    struct header currHead; 
    memcpy(&currHead, ((char*)(ptr)-sizeof(struct header)), sizeof(struct header));

    if(currHead.freed == 1){ // freeing a pointer that is already free
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    currHead.freed = 1;
    memset(ptr, '\0', currHead.size);
    memcpy(((char*)(ptr) -sizeof(struct header)), &currHead, sizeof(struct header));

    // coalescing: 

    // checks to see if the chunk after the current one if free as well
    if(((char*)(ptr) + currHead.size) <= (char*)(heap.bytes + MEMLENGTH - sizeof(struct header))){ // checks if a next header exists
        struct header nextHead;
        memcpy(&nextHead,ptr+currHead.size,sizeof(struct header));
        if(nextHead.freed == 1){
            currHead.size += (sizeof(struct header) + nextHead.size); // increments size of header thats first
            memcpy(((char*)(ptr) - sizeof(struct header)), &currHead, sizeof(struct header)); // copies header back to heap
        }
    }

    // checks to see if the chunk before is free as well
    if((char *)ptr - sizeof(struct header) > (char *)heap.bytes){
        struct header *currPtr;         
        struct header *prevPtr = (struct header*)(heap.bytes);
        struct header prevHeader;
        memcpy(&prevHeader, prevPtr, sizeof(struct header));

        for(int i = (sizeof(struct header) + prevHeader.size); i<=MEMLENGTH-8;){ 
            
            currPtr = (struct header*)(heap.bytes + i); 
            memcpy(&currHead, currPtr, sizeof(struct header));

            if(currPtr == ptr-sizeof(struct header)){ // finds the header before the current one
                if(prevHeader.freed == 1){ // checks to see if that is a free chunk
                    prevHeader.size += (sizeof(struct header) + currHead.size);
                    memcpy(prevPtr,&prevHeader,sizeof(struct header));
                }
                break;
            }

            prevPtr = currPtr;
            memcpy(&prevHeader,prevPtr,sizeof(struct header));            
            i += (currHead.size + sizeof(struct header)); 
        }
    }

}


