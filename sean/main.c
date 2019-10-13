/* PROJECT EULER PROBLEM 389
An unbiased single 4-sided die is thrown and its value, T, is noted.
T unbiased 6-sided dice are thrown and their scores are added together.
  The sum, C, is noted.
C unbiased 8-sided dice are thrown and their scores are added together.
 The sum, O, is noted.
O unbiased 12-sided dice are thrown and their scores are added together.
 The sum, D, is noted.
D unbiased 20-sided dice are thrown and their scores are added together.
 The sum, I, is noted.
Find the variance of I, and give your answer rounded to 4 decimal places.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "dice.h"


int main(int argc, char** argv){
  MPI_Init(NULL, NULL);
  int rank, nprocs;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &nprocs);
  MPI_Comm_rank(world, &rank);

  if(argc < 2){
    if (rank == 0) printf("Useage: ./[Executable] [Iterations Per Process]\n\n");
    return 1;
  }
  printf("nprocs: %d\n", nprocs);

  int *all_I = malloc(sizeof(int) * atoi(argv[1]));
  // if(rank==0){
    int i;
    for(i=0;i<atoi(argv[1]);i++){
      all_I[i] = rollTheDice();
    // }

    for(i=0;i<atoi(argv[1]);i++){
      printf("(%d)all_I[%d]: %d\n", rank, i, all_I[i]);
    }

    }

    MPI_Finalize();
    // if(rank == 0)   printTree(&tree.root, 0);
    return 0;
}
