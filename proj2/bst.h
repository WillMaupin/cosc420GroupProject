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
    tree->root = NULL;
}

/*insertBSTNode:
    recursively inserts into tree alphabetically: words that appear
    earlier alphabetically will be inserted to the left, words that appear
    later will be inserted to the right.

    RETURNS:
        BSTNode*: have to reassign tree when function is called...
            not sure why...

    ARGUMENTS:
        parent_node: compare keyword of this node with node being inserted,
            also used to point to node after being inserted
        node: node to be inserted   */

BSTNode* insertBSTNode(BSTNode *parent_node, BSTNode* node){
    printf("Welcome to insertBSTNode!!!\n"); // dbugging

    if(node != NULL)        printf("inserting: %s\n", node->keyword); // dbugging
    if(parent_node != NULL) printf("comparing: %s\n", parent_node->keyword); //dbugging

    if(parent_node == NULL) {
        /*  tree is empty, just need to insert node at root */
        // printf("Empty tree\n"); //dbugging
        return node;
    }else{
        /* tree is not empty */

        // printf("tree not empty\n"); //dbugging
        /* determines difference in ascii values between root keyword and keyword of
            node being inserted */

        int key = strcmp(parent_node->keyword, node->keyword);
        printf("%d\n", a); //dbugging
        if(key <= -1){
            //str comes before ptr->keyword alphabetically
            // printf("after\n");

            parent_node->right = insertBSTNode(parent_node->right, node);
            return parent_node;

        } else if (key >= 1){
            //str comes after ptr->keyword alphabetically
            // printf("before\n");

            parent_node->left = insertBSTNode(parent_node->left, node);
            return parent_node;

        } else {
            // str and ptr->key word are the same word
            // printf("equal\n");

            /* add article to nodes linked list here */
            return parent_node;

        }
    }

    // printf("end\n");    // dbugging
}

/*displayBST:

    recursively prints keywords of nodes in preorder

    ARGUMENTS:
        BSTNode *node:
            node to recurse on (if it has any children)
                or print keyword of.

        int level:
            level of tree (increases as you move down the tree,
                s.t.:
                    root is on level 0,
                    roots children on level 1,
                    roots grandchildren on level 2,
                    etc.)
*/
void displayBST(BSTNode *node, int level){
    if(node->left != NULL){
        displayBST(node->left, level++);
    }

    if(node != NULL){
        printf("%d: %s\n", level, node->keyword);
    }else{  printf("null\n"); }

    if(node->right != NULL){
        displayBST(node->right, level++);
    }
}

#endif
