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
#include <math.h>
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

  srand(time(0) + rank/* + 200*/);
  // int *all_I = malloc(sizeof(int) * atoi(argv[1]));
  int iterations = atoi(argv[1]);
  int *local_I = malloc(sizeof(int) * iterations);
  int *root_I = malloc(sizeof(int) * iterations * nprocs);
  double *sqrd_diff = malloc(sizeof(double) * iterations * nprocs);
  int i,j,k;

  for(i=0; i<iterations; i++){
    local_I[i] = rollTheDice();
  }

  if(rank != 0){
    MPI_Send(local_I, iterations, MPI_INT, 0, 0, world);
  }else{
    for(i = 0; i<nprocs; i++){
      int *temp = malloc(sizeof(int) * iterations);
      if(i!=0)  MPI_Recv(temp, iterations, MPI_INT, i, 0, world, MPI_STATUS_IGNORE);

      for(j = 0; j<iterations; j++){
        if(i == 0){
          root_I[j] = local_I[j];
          sqrd_diff[j] = local_I[j];
          // printf("root_I[%d]: %d\n", j, root_I[j]);
          // printf("sd[%d]: %d\n", j, sqrd_diff[j]);
        }else{
          root_I[iterations * i + j] = temp[j];
          sqrd_diff[iterations * i + j] = temp[j];
          // printf("temp[%d]: %d\n", j, temp[j]);
          // printf("root_I[%d]: %d\n", iterations * i + j, root_I[iterations * i + j]);
          // printf("sd[%d]: %d\n", iterations * i + j, sqrd_diff[iterations * i + j]);
        }
      }
    }


    double mean = 0;
    double variance = 0.0;

    if(rank==0){
      for(i = 0; i<iterations*nprocs; i++){
        // printf("s root_I[%d]: %d\n", i, root_I[i]);
        // printf("sd[%d]: %d\n", i, sqrd_diff[i]);
        mean += root_I[i];
        // if(i%3 == 2) puts("");
      }

      mean /= (iterations * nprocs);

      for(i = 0; i<iterations*nprocs; i++){
        // printf("\nmean: %d\n", mean);
        // printf("rt[%d]: %d\n", i, root_I[i]);
        // printf("sd[%d]: %d\n", i, sqrd_diff[i]);
        sqrd_diff[i] -= mean;
        // printf("- mean[%d]: %d\n", i, sqrd_diff[i]);
        sqrd_diff[i] *= sqrd_diff[i];
        // printf("sqrt diff[%d]: %d\n", i, sqrd_diff[i]);
        // if(i%3==2) puts("");
        variance += sqrd_diff[i];
        // printf("variance: %f\n\n", variance);
      }

      variance /= (nprocs*iterations)-1;
      // printf("mean: %f\n", mean);
      // float
      printf("final variance: %f\n", variance);
      printf("expected variance: %f\n", ev);
      printf("difference: %f\n", ev - variance);
    }
  }
  /*variance:
    -find the mean (above)
    -for each number, subtract the mean and square the result
        (the squared difference)
    -find average of those squared differences
  */
  // }


  MPI_Finalize();
  return 0;
}
