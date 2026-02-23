#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertFront(Node** head, int data);
void removeFront(Node** head);

#endif