#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "bst.h"
// #include "node.h"



int main(){
    BSTree tree;
    initBST(&tree);


    // insertBSTNode1(&tree, "keyword");

    BSTNode a = {0, "keyword", NULL, NULL, NULL };
    insertBSTNode2(tree.root, &a);
    printf("\n");
    if(tree.root)   printf("%s\n", tree.root->keyword);
    else            printf("null\n");
    // displayBST(tree.root);

    // insertBSTNode1(&tree, "sean");

    // BSTNode b = {1, "sean", NULL, NULL, NULL };
    // insertBSTNode2(tree.root, &b);
    // displayBST(tree.root);

    // char* a = malloc(sizeof(char) * 5);
    // char* b = malloc(sizeof(char) * 5);
    //
    // printf("%d\n", strcmp(a,a));

    return 0;
}
