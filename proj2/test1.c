#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<mpi.h>

#include "bst.h"

/*printBST()
    mostly used to format ouput for debugging
    ARGUMENTS:
        BSTree tree:
            BSTree to be printed, passes root node of tree
            to bst.displayBST()

    RETURNS:
        n/a
*/
void printBST(BSTree tree){
    printf("\n============= tree (preorder) ==============\n");
    displayBST(tree.root, 0);
    printf("============================================\n");
}

int main(){
    MPI_Init(NULL, NULL);

    BSTree tree;
    initBST(&tree);

    // BSTNode a;
    // initBSTNode(&a, "mmmm");

    // tree.root = insertBSTNode(tree.root, &a);
    tree.root = insert(tree, "mmmm");
    // tree.root = insert(tree, "matt");
    // tree.root = insert(tree, "will");
    // tree.root = insert(tree, "sean");

    printf("%s\n", tree.root->keyword);
    tree.root->left = NULL;
    tree.root->right = NULL;

    if(tree.root->left != NULL) printf("tree.root->left\n");
    if(tree.root->right != NULL)printf("tree.root->right\n");
    if(tree.root->articles != NULL)printf("tree.root->articles \n");

    /*
    getting inf. recursion when printing... somehow root nodes left pointer is
    not null, assigned null in multiple places...
    */
    // if(tree.root != NULL)   printBST(tree);
    // else    printf("%s\n", "end");


    MPI_Finalize();
    return 0;
}
