#ifndef TREE_H
#define TREE_H

typedef struct TNode {
    int key;
    struct TNode* left;
    struct TNode* right;
} TNode;

TNode* bst_insert(TNode* root, int key);
TNode* bst_remove(TNode* root, int key);
int bst_contains(TNode* root, int key);

#endif