# Lecture 12-1: SMART POINTERS AND THREADS

See the usual slides PDF here. It is a lecture in two parts:

### Part 1: smart pointers (cont'd)


`Slide 01` [Part 01. Recall Smart Pointers](https://ensemble.reed.edu/Watch/n7KGp6y4) *10m15s*  
`Slide 17` [Part 02. `shared_ptr` Box](https://ensemble.reed.edu/Watch/By57GwDx) *04m00s*  
`Slide 27` [Part 03. Singly Link List](https://ensemble.reed.edu/Watch/g4PKf62E) *10m45s*  
`Slide 45` [Part 04. Doubly Linked List](https://ensemble.reed.edu/Watch/Lk5y2R3E) *08m00s*  

The `samples` folder from the last lecture contains the singly-linked
list code `llist.cc`.  It also contains three versions of a
doubly-linked list. One of these, named `dbllist_bad.cc` is
broken. Since all the pointers are `shared_ptr` references, and since
there is a cyclic structure within doubly-linked lists, the nodes
aren't properly deallocated.

The other two fix the `_bad` one in two ways:

* `dbllist_better.cc`: all references are `shared_ptr` here, as well.
But the explicit destructor traverses the list and sets all the 
`prev` links to `nullptr`. This has the effect of breaking any cyclic
structures in the list so that the nodes' `shared_ptr` reference counts 
can go to 0, leading to their reclamation.

* `dbllist_best.cc`: this code instead works with `prev` links of
type `weak_ptr`. These copied references from `shared_ptr` instances
don't increase the reference count. In this way, the `shared_ptr`
structure of the doubly-linked list has no cycles, and so nodes
get reclaimed.

### Part 2: intro to threads

This lecture's `samples` folder contains two programs. Each creates 
*two additional threads* of execution using the POSIX threads (or
*pthreads* C) library. These are as follows

* `walkchew.cc`: runs two independent threads `walk` and `chewGum`
that do their work. On my system, the output from each is interleaved
because the two threads seem to get scheduled concurrently. Either 
that or they regularly preempt each other.

* `count.cc`: Two threads are given the same address in memory. 
They each repeatedly fetch that value from mrmory, add one to it,
then store that incremented value back to that same place in 
memory. Hijinks ensue.

We'll discuss what goes wrong with the `count.cc` in the next lecture.

These can be compiled with the lines

    g++ -o walkchew -lpthread walkchew.cc
    g++ -o count -lpthread count.cc

Feel free to run the latter one to see what happens. See if you can explain
what goes wrong.


