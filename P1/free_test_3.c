#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

void scenario1(){

    // This tests to make sure you cannot free a header more than once
    
    fprintf(stderr,"Scenario 1 should return an error message: \n");

    void* test1 = malloc(80);
    free(test1);
    free(test1);
}

int main(){

    scenario1();
    return 0;
}