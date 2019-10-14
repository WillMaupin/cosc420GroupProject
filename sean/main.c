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
  //fart

  // int *all_I = malloc(sizeof(int) * atoi(argv[1]));
  int iterations = atoi(argv[1]);
  int *local_I = malloc(sizeof(int) * iterations);
  int *root_I = malloc(sizeof(int) * iterations * nprocs);

  for(int i=0; i<iterations; i++){
    local_I[i] = rollTheDice();
  }
  // printf("iterations: %d, it*nprocs: %d\n", iterations, iterations*nprocs);
  // for(i=0; i<iterations; i++){
  //   printf("(%d)local_I[%i]: %d\n", rank, i, local_I[i]);
  // }

  if(rank != 0){
    printf("%d in send", rank);
    MPI_Send(local_I, iterations, MPI_INT, 0, 0, world);
  }else{
    for(int i = 0; i < nprocs; i++){
      for(int j = 0; j<iterations; j++){
        if(i == 0){
          root_I[j] = local_I[j];
          printf("root[%d]: %d\n", j, root_I[j]);
        }else{
          printf("%d in else\n", i);
          int *temp = malloc(sizeof(int) * iterations);
          MPI_Recv(temp, iterations, MPI_INT, i, 0, world, MPI_STATUS_IGNORE);
          // for(int j = 0; j<iterations; j++){
          root_I[iterations * i * j] = temp[j];
          // }
          printf("root_I[%d]: %d\n", iterations * i * j, root_I[iterations * i * j]);
        }
      }
    }
  }

  // MPI_Reduce(&local_I, &root_I, 1, MPI_INT, MPI_SUM, 0, world);
  // if(rank == 0){
  //   printf("root I: %d\n", root_I);
  //   int mean, sqrd_diff, variance;
  //   mean = root_I / (nprocs * atoi(argv[1]));
       /*variance:
          -find the mean (above)
          -for each number, subtract the mean and square the result
            (the squared difference)
          -find average of those squared differences
        */
  //   printf("variance: %d\n", variance);
  // }


  MPI_Finalize();
  return 0;
}
