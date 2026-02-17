#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

#define MEMLENGTH 4096

static int heap_init = 0;

static union {
    char bytes[MEMLENGTH];
    double not_used;
} heap;

void * mymalloc (size_t size, char *file, int line){
    if(heap_init == 0){
        heap_init = 1;

    }


}
void myfree (void *ptr, char *file, int line){
    if(heap_init == 0){
        heap_init = 1; 
    }
}

void initilize_heap(){
    
}
