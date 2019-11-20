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

    BSTree tree = { root:NULL };
    // initBST(&tree);

    BSTNode a = {   keyword:"mmmm",
                    left:NULL,
                    right:NULL,
                    articles:NULL   };

    tree.root = insertBSTNode(tree.root, &a);
    printBST(tree);

/*
    char** words = malloc(sizeof(char*) * 3);
    words[0] = "sean";
    words[1] = "devin";
    words[2] = "matt";
    BSTNode *node = malloc(sizeof(BSTNode));


    for(int i=0; i<2; i++){
        BSTNode temp = {
            keyword: words[i],
            left:NULL,
            right:NULL,
            articles:NULL
        };

        node = &temp;
        tree.root = insertBSTNode(tree.root, node);
        // tree.root = insertBSTNode(tree.root, &temp);

        printBST(tree);
    }
*/

//*
    // BSTNode b = {   keyword:"aaaa",
    //                 left:NULL,
    //                 right:NULL,
    //                 articles:NULL   };

    BSTNode b;
    initBSTNode(&b, "aaaa");
    tree.root = insertBSTNode(tree.root, &b);
    printBST(tree);

    BSTNode c;
    initBSTNode(&c, "zzzz");
    tree.root = insertBSTNode(tree.root, &c);
    printBST(tree);

    BSTNode d;
    initBSTNode(&d, "ssss");
    tree.root = insertBSTNode(tree.root, &d);
    printBST(tree);

//*/

    MPI_Finalize();
    return 0;
}
