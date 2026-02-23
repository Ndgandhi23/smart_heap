#include <stdlib.h>
#include "tree.h"
#include "mymalloc.h"  

static TNode* new_node(int key) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    if (!n) return NULL;

    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

TNode* bst_insert(TNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else if (key > root->key)
        root->right = bst_insert(root->right, key);
    return root;
}

static TNode* find_min(TNode* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

TNode* bst_remove(TNode* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key) {
        root->left = bst_remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = bst_remove(root->right, key);
    }
    else {

        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        if (root->left == NULL) {
            TNode* temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            TNode* temp = root->left;
            free(root);
            return temp;
        }

        TNode* succ = find_min(root->right);
        root->key = succ->key;
        root->right = bst_remove(root->right, succ->key);
    }

    return root;
}