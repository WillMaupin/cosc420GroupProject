#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

clock_t t;
t = clock();
int ierr, pid, np, elements_per_process, n_elements_recieved;

MPI_Status status;
MPI_Init(&argc, &argv);

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &pid);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &np);

//Declare vars for sum and all 16 matrix boxes
int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, sum;
int count=0;

//Set each process a and b to break problem into 100 parts
//Iterate through 7 other cells for each process
a=pid/10; 
b=pid%10;
for(c=0; c<10; c++){
for(d=0; d<10; d++){
for(e=0; e<10; e++){
for(f=0; f<10; f++){
for(g=0; g<10; g++){
for(i=0; i<10; i++){
for(k=0; k<10; k++){

//Calculate sum (reference point) for each iteration with a, b, c, d values
//For all cells outside of for loops calculate by subtracting
//3 other determined values in row, column or diagonal from sum
//Check to make sure value is within range of 0-9
sum = a + b + c + d;
h = sum - e - f - g;
if(h<0 || h>9)
continue;
p = sum - a - f - k;
if(p<0 || p>9)
continue;
m = sum - a - e - i;
if(m>9 || m<0)
continue;
o = sum - c - g - k;
if(o>9 || o<0)
continue;
j = sum - d - g - m;
if(j>9 || j<0)
continue;
l = sum - i - j - k;
if(l<0 || l>9)
continue;
n = sum - b - f - j;
if(n>9 || n<0)
continue;

//Check to make sure sums of all rows, columns and diagonals add up to same value
//If yes increment by 1
if((e+f+g+h)==sum && (i+j+k+l)==sum && (m+n+o+p)==sum && (a+f+k+p)==sum && (d+g+j+m)==sum && (a+e+i+m)==sum && (b+f+j+n)==sum && (c+g+k+o)==sum && (d+h+l+p)==sum){
count = count + 1;
}
}
}
}
}
}
}
}
int total;
//Reduce total count across all nodes
MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
MPI_Finalize();
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
//Print total and time taken
if(pid==0){
printf("Total = %d\n", total);
printf("Time taken = %f\n", time_taken);
}
}
