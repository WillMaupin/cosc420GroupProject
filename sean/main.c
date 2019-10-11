#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#include "tree.h"

// _Bool

int main(int argc, char** argv){
    if(argc == 1){
        printf("Useage: ./[executable] [size of tree] [flags]");
        return 1;
    }else{
        int i;
        for(i=0; i<argc; i++){
            if(strcmp(argv[i], "-d") == 0){
                DBUG = true;
            }
        }
    }

    MPI_Init(NULL, NULL);
    int rank, nprocs;
    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &nprocs);
    MPI_Comm_rank(world, &rank);

    if(DBUG)
        printf("nprocs: %d\nsize: %d\n", nprocs, atoi(argv[1]));

    if(rank==0){
        BinaryTree tree;
        initBTree(&tree, atoi(argv[1]));
    }
    // Node tree;
    // insertNode(&tree.root, 0);

    // genTree(&tree, &tree.root, atoi(argv[1]), 1, 0);


    MPI_Finalize();
    // if(rank == 0)   printTree(&tree.root, 0);
    return 0;
}
