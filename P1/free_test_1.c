#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

void scenario1(){

    // This tests to make sure than you cannot free a random variable that was not allocated via mymalloc
        // Should print an error
    
    fprintf(stderr,"Scenario 1 should return an error message: \n");
    int test8 = 5;
    free(&test8);
}

int main(){
    scenario1();

    return 0;
}