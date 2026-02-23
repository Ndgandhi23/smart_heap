#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"
#include "list.h"
#include "tree.h"

void task1() {
    for(int i = 0; i < 120; i++){
        char *p = malloc(1);
        free(p);
    }
}

void task2() {
    char *array[120]; 
    for(int i = 0; i < 120; i++){
        array[i] = malloc(1);
    }
    for(int i = 0; i < 120; i++){
        free(array[i]);
    }
}

void task3() {
    char *array[120];
    int totalAllocated = 0; 
    int currentAllocated = 0;

    for(int i = 0; i < 120; i++){
        array[i] = NULL;
    }

    while(totalAllocated < 120){
        double r = (double)rand() / RAND_MAX;
        if(currentAllocated != 120 && (r > 0.5 || currentAllocated == 0)){
            int i = 0;
            while(i < 120 && array[i] != NULL){
                i++;
            }
            if(i < 120){
                array[i] = malloc(1);  
                totalAllocated+=1;
                currentAllocated+=1;
            }
        }
        else if(currentAllocated != 0){
            int r_idx = 0;
            do{
                r_idx = rand() % 120;
            }while(array[r_idx] == NULL);

            free(array[r_idx]);
            array[r_idx] = NULL;
            currentAllocated-=1;
        }
    }

    for (int i = 0; i < 120; i++) {
        if (array[i] != NULL) {
            free(array[i]);
            array[i] = NULL;
        }
    }
}

void task4(){
    int currentAllocated = 0;
    Node* head = NULL;
    for(int i = 0; i < 40; i++){
        double r = (double)rand() / RAND_MAX;
        if(r > 0.5 || currentAllocated == 0){
            insertFront(&head, 1);
            currentAllocated++;
        }
        else{
            removeFront(&head);
            currentAllocated--;
        }
    }

    while(head != NULL){
        removeFront(&head);
    }
}

void task5() {
    int currentAllocated = 0;
    TNode* root = NULL;

    int keys[40];
    int nextKey = 1;

    for (int i = 0; i < 40; i++) {
        double r = (double)rand() / RAND_MAX;

        if (r > 0.5 || currentAllocated == 0) {
            int k = nextKey++;              
            root = bst_insert(root, k);
            keys[currentAllocated] = k;        
            currentAllocated++;
        } else {
            int idx = rand() % currentAllocated;
            int k = keys[idx];

            root = bst_remove(root, k);

            keys[idx] = keys[currentAllocated - 1]; 
            currentAllocated--;
        }
    }

    while (currentAllocated > 0) {
        int k = keys[currentAllocated - 1];
        root = bst_remove(root, k);
        currentAllocated--;
    }
}
    



int main(){
    srand((unsigned)time(NULL));

    struct timeval start, end;
    long time_taken;

    gettimeofday(&start, NULL);

    for(int i = 0; i < 50; i++){
        task1();
        task2();
        task3();
        task4();
        task5();
    }

    gettimeofday(&end, NULL);

    time_taken = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

    printf("Average time per workload: %.2f microseconds\n", (double)time_taken / 50.0);

    return 0;
}