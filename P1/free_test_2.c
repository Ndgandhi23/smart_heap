#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

void scenario1(){

    // This tests to make sure than you cannot free a random pointer that is not associated with a header
        // Should print an error and leak detection should return 
    
    fprintf(stderr,"Scenario 1 should return an error message and leak message: \n");
    void *test1 = malloc(64);
    free(test1 + 1);
}

int main(){
    scenario1();
    return 0;
}