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
BSTNode* insertBSTNode(BSTNode *root_node, BSTNode* new_node){
    printf("Welcome to insertBSTNode!!!\n"); // dbugging

    if(new_node != NULL)    printf("inserting: %s\n", new_node->keyword); // dbugging
    if(root_node != NULL)   printf("comparing: %s\n", root_node->keyword); //dbugging

    if(root_node == NULL) {
        /*  tree is empty, just need to insert node at root */
        printf("Empty tree\n"); //dbugging

        // node = new_node;
        return new_node;
    }else{
        /* tree is not empty */
        printf("tree not empty\n"); //dbugging

        /* determines difference in ascii values between root keyword and keyword of
            node being inserted */
        int key = strcmp(root_node->keyword, new_node->keyword);
        printf("%d\n", key); //dbugging
        if(key <= -1){
            //str comes before ptr->keyword alphabetically
            printf("after\n");

            root_node->right = insertBSTNode(root_node->right, new_node);
            return root_node;

        } else if (key >= 1){
            //str comes after ptr->keyword alphabetically
            printf("before\n");

            root_node->left = insertBSTNode(root_node->left, new_node);
            return root_node;

        } else {
            // str and ptr->key word are the same word
            printf("equal\n");

            /* add article to nodes linked list here */
            return root_node;
        }
    }

    printf("end\n");    // dbugging
}

/*
    tried to rework insertion with this function, to make the function calls
    simpler and remove need to explicitly declare a new node for each
    keyword
        BSTNode a = {...};
            vs.
        insert(tree, <keyword string>);

    idea is to initialize new node in this function, actual insertion is
    done in insertBSTNode
    much of this function is debugging code, left pointer is not NULL
    in main function, shows to be null here though...
    not sure what is going on or why it is happening


*/
BSTNode* insert(BSTree tree, char* str){
    BSTNode new_node;      //new node to be inserted
    initBSTNode(&new_node, str);    //set keyword to str, else to NULL

    /*  debugging
    printf("new_node: %s\n", new_node.keyword);
    if(new_node.left != NULL)       printf("new_node.left\n");
    if(new_node.right != NULL)      printf("new_node.right\n");
    if(new_node.articles != NULL)   printf("new_node.articles \n");

    BSTNode* hold = insertBSTNode(tree.root, &new_node); //used in debugging
    if(hold->left != NULL)          printf("hold->left\n");
    if(hold->right != NULL)         printf("hold->right\n");
    if(hold->articles != NULL)      printf("hold->articles \n");
    return hold;     //debugging

    debug code ends here*/

    return insertBSTNode(tree.root, &new_node); //remove to test code above

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
    printf("a\n");
    if(node->left != NULL){
        printf("b\n");
        // displayBST(node->left, level++);
        printf("c\n");
    }
    printf("d\n");

    if(node != NULL){
        printf("e\n");
        printf("%d: %s\n", level, node->keyword);
        printf("f\n");
    }
    else{  printf("null\n"); }  //debugging
    printf("g\n");

    if(node->right != NULL){
        printf("h\n");
        displayBST(node->right, level++);
        printf("i\n");
    }
    printf("j\n");
}

#endif
