COMP 4001 Assignment 1

"The goal of this assignment is to write a CILK++ program to solve the Towers of Hanoi problem in parallel, using the recursive solution.

The Towers of Hanoi problem and its recursive solution are explained here: http://en.wikipedia.org/wiki/Tower_of_Hanoi."

All code by Damjan Markovic, based on cilk_template code provided.

The code started getting slow at around n = 20 (so 2^20 - 1 steps, thats roughly 1 000 000).
I ran the code on my machine which has only 2 cores. 

The time it took to run the code for n = 21 sequentially was 3778193447 ns, in parallel 2945080165 ns.

So the speed up runnning on 2 cores appears to be:

S(2) = 3778193447/2945080165 = 1.28288305


I split the sequential and parallel programs into 2 seperate .cpp files (seqhanoi.cpp and parhanoi.cpp respectively).

To compile:

Execute the following commands,

g++ parhanoi.cpp -O3 -fcilkplus -o par
g++ seqhanoi.cpp -O3 -o seq


To run:

To achieve the results I got in parallel_tests1.txt and sequential_tests1.txt these are the run commands I executed,

./par 3 4 20 21
./seq 3 4 20 21

So you pass 4 parameters to the executables. The first 2 are for small values of n which can be realistically
written to a file, the last 2 are for large values of n.



