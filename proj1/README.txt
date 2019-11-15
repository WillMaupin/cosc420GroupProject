Matt Adams
Sean Brittingham
Will Maupin
github: github.com/seanbritt4/cosc420GroupProject

Problem: 166
Problem: 372
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
