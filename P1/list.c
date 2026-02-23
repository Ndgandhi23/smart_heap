#include <stdlib.h>
#include "list.h"
#include "mymalloc.h" 

Node* createNode(int data) {
    Node* n = malloc(sizeof(Node));   
    if (!n) return NULL;

    n->data = data;
    n->next = NULL;
    return n;
}

void insertFront(Node** head, int data) {
    Node* n = createNode(data);
    if (!n) return;

    n->next = *head;
    *head = n;
}

void removeFront(Node** head) {
    if (head == NULL || *head == NULL) return;

    Node* temp = *head;       
    *head = (*head)->next; 
    free(temp);          
}