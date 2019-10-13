#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#include "tree.h"

int main(int argc, char** argv){
    if(argc == 1){
        printf("Useage: ./[executable] [size of tree] [flags]");
        return 1;
    }else{

    }

    MPI_Init(NULL, NULL);
    int rank, nprocs;
    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &nprocs);
    MPI_Comm_rank(world, &rank);

    printf("nprocs: %d size: %d\n", nprocs, atoi(argv[1]));

    if(rank==0){
      int k = atoi(argv[1]);
      struct Node *root = newNode(0);
      genTree(root, k);
      // printf("main n %d\n", root->id);
      pre(root);

    }

    MPI_Finalize();
    // if(rank == 0)   printTree(&tree.root, 0);
    return 0;
}
