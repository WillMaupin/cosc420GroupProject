#ifndef BST
#define BST

#include<stdio.h>
#include<stdlib.h>

#include"BSTNode.h"

typedef struct BSTree {
    BSTNode* root;

    // char*

} BSTree;

void initBST(BSTree *tree) {
    // BSTNode root;
    // initBSTNode(&root, 0);
    // tree->root = &root;
    //
    // printf("bst init %d\n", tree->root->id);

    tree->root = NULL;
}

/*
void insertBSTNode1(BSTree* tree, char* str){
    BSTNode temp;
    initBSTNode(&temp, str);

    BSTNode* ptr;
    ptr = tree->root;

    printf("inserting: %s\n", temp.keyword);
    if( ptr != NULL ) printf("comparing: %s\n", ptr->keyword);

    if ( ptr == NULL ) {
        //tree is empty, just need to insert node at root
        printf("Empty tree\n");
        tree->root = &temp;
    } else {
        printf("tree not empty\n");
        int a = strcmp(ptr->keyword, str); //temp variable name, needs a better one
        printf("%d\n", a);
        if(a < 0){
            //str comes before ptr->keyword alphabetically
            printf("before\n");


        } else if (a > 0){
            //str comes before ptr->keyword alphabetically
            printf("after\n");


        } else {
            // str and ptr->key word are the same words
            printf("equal\n");


        }
    }
}
*/


void insertBSTNode2(BSTNode *root_node, BSTNode* node){
    printf("Welcome to insertBSTNode2!!!\n");
    // BSTNode* ptr;
    // ptr = root;

    printf("before\n");
    if(node != NULL) printf("inserting: %s\n", node->keyword);
    printf("during\n");
    if(root_node != NULL) printf("comparing: %s\n", root_node->keyword);
    printf("after\n");

    if ( root_node == NULL ) {
        //root is empty, just need to insert node at root
        root_node = node;
        printf("Empty tree\n");
    } else {
        printf("tree not empty\n");
        int a = strcmp(root_node->keyword, node->keyword); //temp variable name, needs a better one
        printf("%d\n", a);
        if(a < 0){
            //str comes before ptr->keyword alphabetically
            printf("after\n");
            insertBSTNode2(root_node->left, node);

        } else if (a > 0){
            //str comes before ptr->keyword alphabetically
            printf("before\n");
            insertBSTNode2(root_node->right, node);

        } else {
            // str and ptr->key word are the same words
            printf("equal\n");


        }
    }

    printf("end\n");
}

/*
    TODO: ?
*/
void displayBST(BSTNode *node){
    // BSTNode* ptr;

    if(node->left)  displayBST(node->left);
    // printf("displayBST: ");
    printf("%s\n", node->keyword);
    // displayBSTNode(node);
    if(node->right) displayBST(node->right);

}

#endif
