# wwu-ps-parallel-merge-sort
This project implements merge sort as an parallel algorithm.
First of all a (pseudo) random number list is generated
and after that the list is sorted by merge sort.
As long as the size of the list parts are big enough
a new thread is created in each step.
After sorting both parts are merged inplace.