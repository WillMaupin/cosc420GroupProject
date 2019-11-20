#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdlib.h>
#include<stdio.h>

// enum colors { red, black };    // red=0, black=1

typedef struct BSTNode {
    // char* data;

    // int id; //used for debugging

    char* keyword;

    struct BSTNode *left,       //left child pointer
                    *right,     //right child pointer
                    *articles;  //linked list of articles containing this keyword

    /*
        red/black tree stuff is low priority, just putting
        it in as i go but focusing on bst first
    */
    // enum colors color;

} BSTNode;

/*initBSTNode
    ATTN: untested, have been using inline declarations:
    ex:
        BSTNode a = {keyword:<string>,...};
*/
void initBSTNode(BSTNode* node, char* str){
    node->keyword = str;
    node->left = NULL;
    node->right = NULL;
    node->articles = NULL;
}


void displayBSTNode(BSTNode *node) {
    printf("%s\n", node->keyword);
}


#endif
