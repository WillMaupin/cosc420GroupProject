#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include "bst.h"
#define INDEX(n,m,i,j) m*i + j
#define ACCESS(A,i,j) A->arr[INDEX(A->rows, A->cols, i, j)]

void matrixMult(matrix *mat1, matrix *mat2, matrix *multRes){
    //must do dot product method
    int i, j, k, m; // for loop variables
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    float* arr1 = (float*) malloc(mat1->cols*sizeof(float)); // holds a row from matrix1
    float* arr2 = (float*) malloc(mat1->cols*sizeof(float)); // holds a column from matrix2
    int *sendcounts, *sendcounts2, *displs, *displs2, blocksize, leftover, leftover2;
    for(m = 0; m < multRes->rows; m++){
        for(j = 0; j < multRes->cols; j++){
            
            sendcounts = malloc(sizeof(int)*size);
            displs = malloc(sizeof(int)*size);
            sendcounts2 = malloc(sizeof(int)*size);
            displs2 = malloc(sizeof(int)*size);
            blocksize = mat1->cols / size; // number of elements to be sent from mat1
            leftover = (mat1->rows*mat2->cols)%size; // elements left over in matrix 1
            leftover2 = (mat1->rows*mat2->cols)%size; // elements left over in matrix 2
            
            
            //   printf("world size: %d\n\n", size);
            // calculate send counts and displacements
            for(i = 0; i < size; i++){
                if( i == size - 1)
                    sendcounts[i] = blocksize + leftover;
                else
                    sendcounts[i] = blocksize;
                displs[i] = blocksize * i;
            }
            
            for(i = 0; i < size; i++){
                if( i == size - 1) // if last node, receive leftover contents
                    sendcounts2[i] = blocksize + leftover2;
                else
                    sendcounts2[i] = blocksize;
                displs2[i] = blocksize * i;
            }
            
            float rec_buf[sendcounts[rank]];          // buffer where the received data should be stored
            for(i = 0; i < sendcounts[rank]; i++ )
					rec_buf[i] = 0;
            float rec_buf2[sendcounts2[rank]];          // buffer where the received data should be stored
            for(i = 0; i < sendcounts2[rank]; i++ )
					rec_buf2[i] = 0;
            
            //NOTE: POPULATE ARR1 AND ARR2
            for(k = 0; k < mat1->cols; k++){
                arr1[k] = mat1->arr[(m*mat1->cols)+k];
                arr2[k] = mat2->arr[(k*mat2->cols)+j];
            }
            // divide the data among processes as described by sendcounts and displs
            MPI_Scatterv(arr1, sendcounts, displs, MPI_FLOAT, rec_buf, sendcounts[rank], MPI_FLOAT, 0, MPI_COMM_WORLD);
            MPI_Scatterv(arr2, sendcounts2, displs2, MPI_FLOAT, rec_buf2, sendcounts[rank], MPI_FLOAT, 0, MPI_COMM_WORLD);
            
            float partialsum = 0;//value that will hold the partial inner product is instantiated in each node
            for (k = 0; k < sendcounts[rank]; k++){//partial inner product
                // 	  	printf("Multiplying %lf by %lf in rank %d\n", rec_buf[k], rec_buf2[k], rank);
                partialsum += (rec_buf[k] * rec_buf2[k]);
                //       printf("Partial sum of %d is now %lf\n", rank, partialsum);
            }
            
            float global_sum;
            MPI_Reduce( //MPI_Allreduce is not needed. It would only be needed if the results needed to be redistributed to nodes other than root.
            &partialsum,
            &global_sum,
            1,
            MPI_FLOAT,
            MPI_SUM,
            0,
            MPI_COMM_WORLD);
            
            if (rank == 0){//find partial inner product of leftover data in root, add to global sum, output global sum
                ACCESS(multRes, m, j) = global_sum;
            }
        }
    }
    
    //dynamically allocated matrices must have their data freed
      free(sendcounts);
      free(displs);
      free(sendcounts2);
      free(displs2);
      free(arr1);
      free(arr2);
}

void main(){ 
	MPI_Init(NULL,NULL);
	int rank, world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	struct matrix A, B, C, T;
	initEmptyMatrix(&T, 3, 3);
	my(&A, 3, 3);
	initOneMatrix(&B, 3, 1);
	initEmptyMatrix(&C, 3, 1);
	//initOneMatrix(&C, 3, 1);
	hits(&A, &B, &C, &T,rank);
	MPI_Finalize();
}
