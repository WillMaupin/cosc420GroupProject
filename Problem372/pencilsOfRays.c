#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>


//Set the minimum and maximum values for the grid here
#define MIN 0 
#define MAX 100000


//This is the summation for calculating how many columns each processor should cover
unsigned long long sum(unsigned long long m, unsigned long long n){
	return (n-m+1)*(MAX - MIN) - ((n*(n+1))/2) + ((m*(m+1))/2);
}

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);

	MPI_Comm world = MPI_COMM_WORLD;

	int nprocs, me;
	MPI_Comm_size(world, &nprocs);
	MPI_Comm_rank(world, &me);

	clock_t begin;
	if(me == 0)
		begin = clock();

	unsigned long rangeMax = MAX; //maximum value for the range
	unsigned long rangeMin = MIN; //minimum value for the range
	unsigned long rowSize = rangeMax - rangeMin; //how many values will be in each of the rows

	unsigned long numElements = (rangeMax - rangeMin) * (rangeMax - rangeMin); //square the rowSize to get the total number of possible odd elements (of course the actual answer will be about 3/10ths this)


	unsigned long estimatedPerProc = (numElements / 2) / nprocs; //the projected value for the number of elements to send to each process. This won't be exact, but is a close estimate

	unsigned long myRange[2*nprocs]; //to store the ranges for each of the processes

	unsigned long m, n; //m and n will temporarily keep track of the sub-ranges that each process will cover
	m = 0;
	n = -1;	
	unsigned long long procSum, prevSum; 
	prevSum = 0;
	if(me == 0){
		for(int i = 0; i < nprocs; i++){
			do{
				n++;
				procSum = sum(m, n);
			} while(procSum <= (estimatedPerProc - rowSize));
			
			if(i == 0)
				myRange[0] = MIN;
			else
				myRange[i*2+0] = m;
			myRange[i*2+1] = n;
			if(i == nprocs-1)
				myRange[i*2+1] = MAX;
			m = n+1;
			prevSum = procSum;
		}
		for(int i = 0; i < nprocs; i++)
			MPI_Send(myRange+(i*2), 2, MPI_UNSIGNED_LONG, i, 0, world);
	}
		
	if(me != 0){
		MPI_Recv(myRange, 2, MPI_UNSIGNED_LONG, 0, 0, world, NULL);
	}
	printf("Proc %d min %lu\n", me, myRange[0]);
	printf("Proc %d MAX %lu\n", me, myRange[1]);
	
	if(me == 0){
		myRange[0] += 1;
	}
	unsigned long long localTotal = 0;
	for(unsigned long x = myRange[0]; x <= myRange[1]; x++){
		for(unsigned long y = MIN; y <= MAX; y++){
			if(y < x)
				y = x; //skip values that will never be odd
			if((((y*y) / (x*x)) % 2) == 1)
				localTotal++; //if equation evaulates to odd, add one to the local running sum

		}
	}
	
	unsigned long long total;
	MPI_Reduce(&localTotal, &total, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, world); //reduce the local totals down to one value

	clock_t end;
	if(me == 0){
		end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Total is %llu\nProcess took %f seconds\n", total, time_spent);
	}

	MPI_Finalize();
	return 0;
}
