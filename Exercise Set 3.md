# Exercise Set 3
## Exercise 3.2:  Application Exploration
> Write and briefly explain 10 applications of heaps that were not 
discussed in class (note that “heaps” in memory management are NOT 
the same as the heap data structure covered in class.)

1. **Finding the K largest elements in an array** by iterating 
through the array, maintaining a heap of size K that contains the
largest elements
2. **Graph Algorithms**: many graph algorithms (e.g. Dijkstra's 
algorithm) are implemented using heaps
3. **Lossless File Compression**: Huffman coding uses a min-heap to 
compress files
4. **Medical applications** use heaps to store important patientmation
based on priority
5. **Load Balancers** use heaps to store tasks and their priorities, 
and to assign the next-highest task
6. **Resource allocation**: computers use heaps to allocate resources 
effectively based on priority
7. **Merging Already-Sorted Lists**: Heaps can be used to efficiently
combine sorted lists or streams of data into a single sorted stream
8. Anything where you need a **resizable** data structure that maintains 
a max- or min-heap property
9. Anything where you need a **time-efficient** (`O(lg n)`) data structure that 
maintains a max- or min-heap property
10. Anything where you need a **space-efficient** data structure that maintains a 
max- or min-heap property

_Sources:
[GeeksForGeeks](https://www.geeksforgeeks.org/applications-of-heap-data-structure/),
[Wikipedia](https://en.wikipedia.org/wiki/Heap_(data_structure)#Applications)_
> Also, write/explain 5 real-world applications where a priority queue could find use.
1. **Event-driven Simulations**: priority queues can be used to simulate situations
in which the priority of an event is the time that it happens. Events can then be
popped off the queue in the order in which they occur.
2. **Robotics**: priority queues are used to plan tasks and the order in which they 
should occur
3. **Artificial Intelligence** utilizes graph theory, and priority queues are 
utilized in certain algorithms such as the A* search algorithm
4. **Medical Systems** maintain heaps based on data collected during triage such that
they may address the most pressing concerns first
5. **Operating Systems** maintain priority queues to schedule tasks and process 
program interrupts (essentially the highest-priority tasks)

_Sources:
[GeeksForGeeks](https://www.geeksforgeeks.org/applications-priority-queue/)_

## Exercise 3.3: To-Do List
See [this file](priority_queue.cpp).

## Bonus Exercise 3.1: D-Ary Heaps
> A d-ary heap is like a binary heap, but (with one possible 
exception) nonleaf nodes have d children instead of two children. In 
all parts of this problem, assume that the time to maintain the 
mapping between objects and heap elements is O.1/ per operation.

### a. Describe how to represent a d-ary heap in an array.
Assuming a 0-indexed array, the parent-child relations are as follows:
- `parent(i) = (i-1)/d`
- `child(i, n) = di + n + 1`, where `n = 0` points to the index of the
leftmost child, and `n = d - 1` points to the index of the rightmost 
child.

### b. Using Big Theta notation, express the height of a d-ary heap of n elements in terms of n and d.
`h = Θ(log_d(n))`. Like in a binary tree where the base of the 
logarithm is the number of children a node may have (2), here, the 
base of the logarithm is d, the number of children a node may have.

### c. Give an efficient implementation of `Extract-Max()` in a d-ary max-heap. Analyze its running time in terms of d and n.
```python
def extractMax(A):
    if A.heapSize == 0:
        throw "heap underflow"
    max = A[0]
    A[0] = A[A.heapSize - 1]
    A.heapSize--
    reheapDown(A, 0)
    return max
```
It is clear to see that every operation is constant time except for
`reheapDown(A, 0)`. Since that function makes $d$ comparisons for 
every iteration and repeats up to $h$ times ($h = log_d(n)$), that
line, as well as the overall function, has a runtime complexity of 
$T(n, d) = O(1) + d \cdot log_d(n)$, or merely, $T(n, d) = O(d \cdot log(n))$

### d. Give an efficient implementation of `Increase-Key()` in a d-ary max-heap. Analyze its running time in terms of d and n.
```python
def increaseKey(A, i, x):
    if A[i] > x:
        throw ArgumentError("bad input")
    A[i] = x
    while i > 0 and A[parent(i)] < A[i]:
        swap(A[parent(i)], A[i])
        i = parent(i)
```
Every operation in this function is constant time except for the 
while loop, which works its way up the tree, swapping the element with
its parent until it is in its proper place. The worst-case scenario is
when you update a leaf to become the root of the tree, which is 
$O(log_d(n))$, or just $O(log(n))$.

### e. Give an efficient implementation of `Insert()` in a d-ary max-heap. Analyze its running time in terms of d and n.
```python
def insert(A, x):
    A[A.heapSize] = x
    A.heapSize++
    while i > 0 and A[parent(i)] < A[i]:
        swap(A[parent(i)], A[i])
        i = parent(i)
```
Every operation in this function is constant time except for the 
while loop, which works its way up the tree, swapping the element with
its parent until it is in its proper place. Its time complexity is
$O(log_d(n))$, or just $O(log(n))$.