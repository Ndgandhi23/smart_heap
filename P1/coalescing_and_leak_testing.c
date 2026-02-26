#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"

void scenario1(){

    // Test 1:
        // tests for rounding the size up to the closest multiple of 8
    void* test1 = malloc(2034);
    if(test1 == NULL){
        fprintf(stderr,"\nScenario 1 Test 1 failed.\n");
    }
    memset(test1,'1',2039);
    memset((char *)(test1)+2039,'\0',1);

    // Test 2:
        // Allocates another large chunk of heap.bytes 
        // Sets up a scenario where there is enough space to create a header but not a payload
            // our program creates a header with size 0 in this situation, after the current chunk is allocated
    void* test2 = malloc(2032);

    if(test2 == NULL){
        fprintf(stderr,"\nScenario 1 Test 2 failed.\n");
    }
    memset(test2,'2',2031);
    memset((char *)(test2)+2031,'\0',1);

    size_t roundedTest = (char *)test2 - (char*) test1;
    if(roundedTest == 2048){
        fprintf(stderr,"\nPassed the Rounding Test\n");
    }
    else{
        fprintf(stderr,"\nFailed the Rounding Test: %ld\n",roundedTest);
    }

    // Test 3:
        // testing to make sure allocations do not overlap each other
        // do this by comparing test1 to test2's allocations
    
    char firstBit[2040];
    memset(firstBit,'1',2039);
    memset((char *)(firstBit)+2039,'\0',1);
    
    if(strcmp(firstBit,test1) == 0){
        fprintf(stderr,"Scenario 1 passed!\n");
    }
    else{
        fprintf(stderr,"Scenario 1 failed.\n");
    }
    free(test1);
    free(test2);
}

void scenario2(){

    // This tests to see that mymalloc() does not allocate data if there is not enough space

    void* test1 = malloc(2040);
    void* test2 = malloc(2032);
    fprintf(stderr,"Scenario 2 should returns an error message: \n");
    void* test3 = malloc(8);

    if(test3 == NULL){
        fprintf(stderr,"Scenario 2 passed!\n");
    }
    else{
        fprintf(stderr,"Scenario 2 failed.\n");
    }

    free(test1);
    free(test2);
}

void scenario3(){
    // Tests coalsecing because there should be the freed chunk from before and a header with size 0 after
        // in our program, it allows for there to be a header that is free of payload size 0 (in README) 
    // Tests coalescing of free chunks before and after the current chunk freed 
        // If you can allocate test3 = malloc(4088) that means that coalescing occured 
            // because there was a block large enough to account for that size

    void* test1 = malloc(2040);
    void* test2 = malloc(2032);
    free(test1); // basic free
    free(test2); // should coalesce with test1's freed chunk and the empty header after test2's chunk

    void* test3 = malloc(4088);
    if(test3 == NULL){
        fprintf(stderr,"Scenario 3 failed.\n");
    }
    else{
        fprintf(stderr,"Scenario 3 passed!\n");
        free(test3);
    }

}

void scenario4(){
    // This tests Leak Detection by not freeing an allocated chunk 
        // and seeing if it appropriately returns the bytes leaked into objects message
    fprintf(stderr,"Scenario 4 should return a leak error message: \n");
    void* test9 = malloc(80);
}

int main(){

    scenario1();
    scenario2();
    scenario3();
    scenario4();

    return 0;
}
