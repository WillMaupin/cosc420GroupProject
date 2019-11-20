#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<mpi.h>

#include "bst.h"

int main(){
    MPI_Init(NULL, NULL);

    BSTree tree = { root:NULL };
    // initBST(&tree);

    BSTNode a = {   keyword:"mmmm",
                    left:NULL,
                    right:NULL,
                    articles:NULL   };

    tree.root = insertBSTNode(tree.root, &a);
    printf("\n============= tree (preorder) ==============\n");
    displayBST(tree.root, 0);
    printf("============================================\n");

/*
    BSTNode b = {   keyword:"aaaa",
                    left:NULL,
                    right:NULL,
                    articles:NULL   };

    tree.root = insertBSTNode(tree.root, &b);
    printf("\n============= tree (preorder) ==============\n");
    displayBST(tree.root, 0);
    printf("============================================\n");

    BSTNode c = {   keyword:"zzzz",
                    left:NULL,
                    right:NULL,
                    articles:NULL   };

    tree.root = insertBSTNode(tree.root, &c);

    printf("\n============= tree (preorder) ==============\n");
    displayBST(tree.root, 0);
    printf("============================================\n");


    BSTNode d = {   keyword:"ssss",
                    left:NULL,
                    right:NULL,
                    articles:NULL   };

    tree.root = insertBSTNode(tree.root, &d);

    printf("\n============= tree (preorder) ==============\n");
    displayBST(tree.root, 0);
    printf("============================================\n");
*/

    MPI_Finalize();
    return 0;
}
