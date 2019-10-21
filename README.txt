Matt Adams
Sean Brittingham
Will Maupin
github: github.com/seanbritt4/cosc420GroupProject

Problem: 166

Initially wanted to solve problem sequentially before moving on to a parallel
solution. First thought was to iterate through a 16 slot array counting
upwards through 10^16 possible matrixes. 
This clearly wasn't a feasible option as there were too many values to iterate
through, so had to continue looking for a solution.
Then noticed that 6 exterior sums (H, L, P, M, N, O)

	  a b c d
	  e f g H
	  i J k L
	  M N O P


could be computed by subtracting 3 shared values in the row/column/diagonal 
from a sum (a+b+c+d). 
This saved 6 for loops, making the problem solvable in around a minute
sequentially.
Then noticed sequential time could be even further reduced once M was computed. 
This allowed for j's for loop to also be removed by j = sum - M - g - d.
This brought the time down to ~6 seconds. 
From here, using 100 nodes each calculating 1/100th of the matrix, was able
to get a total count of valid matrixes and reduce them, bringing total time 
to about .3 seconds.
By setting a=processID/10 and b=processID%10 was able to cycle through all
matrix combinations.




Problem: 372

Originally, the program ran on all (10*9 - 2*10^6)^2 = 996.004*10^12 elements, 
which was too many to compute in any reasonable amount of time. Some alternative
solutions to speed this up were to cut the elements in half, effectvely speeding
it up by 2x, and another was to estimate the answer by finding the ratio of odd to
even values on a smaller data set. I found this ratio to be around 0.32, but it was
not accurate enough to provide a correct answer. Furthermore, this ratio seemed to
vary to be less than or greater than 0.32 as the data size increased, which leads
me to belive that it will not converge to a trivial value. However, the ratio never
strayed too far from 0.32, which was interesting nontheless.

To compare the runtimes, a small dataset with a range of (0, 100000) was used, these
are displayed in a table included in the .zip file

Unfortunately, I could not get the program to finish on the full datasize. Further
optimization would need to be done to get a precice answer any faster, and such a 
solution would rely on the geometry or algebra of the problem, which is difficult
to determine. The process did not get to run for its full 24 hour time slot, 
around hour 18 it received an error "ORTE has lost communication with a remote 
daemon." The full error is in the .log file included in the zip file. 

As far as arithmetic complexity is concerned, splitting the data between the 
processes takes Big_Theta(nprocs * rowsize/nprocs) operations = Big_Theta(rowsize) -> 
Big_Theta(N), where 
rowsize = (10*9 - 2*10^6) for the full data size
And the actual computations for determining the result require Big_theta((rowsize^2) * 8) = 
Big_Theta((N^2)/8) = O(N^2)


Problem: 389, 30% difficulty - Sean Brittingham
================================================================================
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
================================================================================

BEST ATTEMPT SO FAR:
  bash-4.2$ cat out/1577.log
  nprocs: 256

  calculated v: 2406428.7106
  ===============================
  expected   v: 2406376.3623
  difference:   -53.3483
  ===============================

NOTE: I was unable to calculate a consistent figure for the variance of I. Because
of this, I found the actual solution online, and used this to calculate the
difference between the value that my program calculated and the expected value.

Most of the changes that I made to this program came from my understanding of
variances. At first I hoped to use MPI_Gather but realized that I would need to
store the I-values as they were calculated and access them again later on. I had
also hoped to research a more mathematical approach to this problem but ultimately
was unable to implement anything other than a mostly bruteforce solution. I used
MPI_Send to send a processors local array of I-values to the root process, and
MPI_Recv in the root process to receive incoming arrays and stored them all in a
single array, which is where the remaining calculations were performed.

total operations:
Problem: 697


This problem proved to be too difficult for us to figure out with the time alloted.
We figured out a brute force method to solve it, however it would have taken
even longer than the pencils of rays problem to solve. We wrote python scripts
to determine all of the strings we would need to compute on, but considering the 
length of these strings and how many there were, we decided to continue to focus 
on our own problems. 

There was an algorithm for this problem that we wrote that we're actually sort of proud of,
this is in the distStars.py file, included in the zip. It distributes the number
of stars (as in a regular expression, where a number represents how many wildcard
characters can be placed inbetween the characters of the full string), and calculates
all of the distributions while keeping all of them unique. Permutation of these strings 
was also required for our (incomplete) implementation of this problem, and is in 
permuteTest.c. Ideally, this file would do a permutation of all of the strings created 
by distStars.py.

So although much of the work required to finish this problem is yet to be done, 
parallelizing it would require only a few hours of mental labor (as much of it
has been done already) and very, very many computer-hours

