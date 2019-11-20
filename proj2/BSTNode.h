#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdlib.h>
#include<stdio.h>

typedef struct BSTNode {
    // char* data;

    int id; //used for debugging

    char* keyword;
    char* abstract;

    struct BSTNode *left, *right;

} BSTNode;

void initBSTNode(BSTNode* node, char* str){
    node->keyword = str;

    node->left = NULL;
    node->right = NULL;
}

void displayBSTNode(BSTNode *node) {
    printf("%s\n", node->keyword);
}


#endif
