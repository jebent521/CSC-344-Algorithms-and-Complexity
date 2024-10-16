# Algorithms Collection Sheet
## Insertion Sort
#### Tweet Summary
For each element in the array, insert it into the sorted subarray, 
which will grow until it's the size of the array.

#### Pseudocode
```python
def InsertionSort(array):
    for i in range(1, len(array)):
        key = array[i]
        j = i - 1
        
        # Move elements of array[0..i-1], that are greater than key,
        # to one position ahead of their current position
        while j >= 0 and array[j] > key do
            array[j + 1] = array[j]
            j = j - 1
        
        # Place the key at the correct position
        array[j + 1] = key
```
#### Why it works
Loop invariant is that it maintains a sorted subarray on the left
* before the loop, everything from 0 to i-1 is sorted
* after the loop, everything from 0 to i is sorted

#### Runtimes
* WCRT: $O(n^2)$ if list is in reverse order
* ACRT: $O(n^2)$
* BCRT: $O(n)$ if list is already sorted

#### Use Cases
Insertion sort is useful for data that's already nearly sorted. It is also a simple
lightweight algorithm so good for when you don't want unneccessary complexity. 

## Merge Sort
#### Tweet Summary
Split the array into two halves, call MergeSort on those halves, then 
merge the two halves together (in sorted order).

#### Pseudocode
```python
# sort entire array using MergeSort(A, 0, len(A) - 1)
def merge_sort(arr, left, right):
    if left < right:
        mid = (left + right) // 2       # mid-point b/n left & right

        merge_sort(arr, left, mid)      # merge_sort left half
        merge_sort(arr, mid + 1, right) # merge_sort right half
        merge(arr, left, mid, right)    # merge the two halves

def merge(arr, left, mid, right): 
    n1 = mid - left + 1         # get size of left half
    n2 = right - mid            # get size of right half

    # Create temp arrays of sizes left and right
    L = [0] * n1
    R = [0] * n2

    # Copy data to temp arrays L[] and R[]
    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]

    i = 0                       # Initial index of left subarray
    j = 0                       # Initial index of right subarray
    k = left                    # Initial index of merged subarray

    # Merge the temp arrays back into arr[left..right]
    while i < n1 and j < n2:
        if L[i] <= R[j]:        # if left element <= right element
            arr[k] = L[i]           # insert left element
            i += 1                  # increment left index
        else:                   # right element < left element
            arr[k] = R[j]           # insert right element
            j += 1                  # increment right index
        k += 1                  # increment merged array index

    # Copy the remaining elements of L[], if there are any.
    # This gets run if j reaches n2 before i reaches n1
    while i < n1:
        arr[k] = L[i]   # insert left element
        i += 1          # increment left & merged indices
        k += 1

    # Copy the remaining elements of R[], if there are any
    # This gets run if i reaches n1 before j reaches n2
    while j < n2:
        arr[k] = R[j]   # insert right element
        j += 1          # increment right & merged indices
        k += 1
```
#### Why it works
It breaks the array in half until it just has single-element arrays,
then re-assembles it in sorted order.

#### Time Complexity
Analysis:
* Splitting array in half is $O(1)$
* MergeSorting both halves is $2T(n/2)$
* Merging the sorted halves is $O(n)$
* So... time complexity is: $O(n \cdot lg(n))$

#### Use Cases
Pros:
* Stable sorting (elements have same relative positions)
* Good for linked lists
* Good on large datasets because of good time complexity

Cons:
* Not a sort-in-place algorithm (non-constant space complexity)

## Bubble Sort
#### Tweet Summary
Moves up the array, bringing the largest element to the top, which 
creates a sorted subarray of the largest values to the right.

#### Pseudocode
```python
def bubbleSort(arr):
    n = len(arr)
    
    # Traverse through all array elements
    for i in range(n):
        swapped = False

        # Last i elements are already in place
        for j in range(0, n-i-1):

            # Traverse the array from 0 to n-i-1
            # Swap if the element found is greater
            # than the next element
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if (swapped == False):
            break
```
#### Why it works
Before each iteration of the loop, the `i` largest elements of the 
array are in sorted order at the top. After each loop iteration, the
`i+1` largest elements of the array are in sorted order at the top.

#### Time Complexity
* WCRT: $O(n^2)$
* ACRT: $O(n^2)$
* BCRT: $O(n)$ if array is already sorted (due to use of `swapped` 
  variable)

#### Use Cases
Pros:
* Stable
* Simple to understand
* Constant space complexity
* Good for small data sets

Cons:
* Slow, bad for large data sets

## Quick Sort
#### Tweet Summary
Picks a partition and puts it in the correct spot in the array, with 
every element less than the partition to its left, and every element
greater than the partition to its right. Then calls quicksort on the
two sides.

#### (Pseudo)code
```c++
// Sorts an array using the quicksort algorithm.
// Initial call: `quicksort(arr, 0, n-1)`, where n is 
// the size of the array
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the index of the pivot
        int pivotIndex = partition(arr, low, high);

        // Quicksort all the elements below the pivot
        quicksort(arr, low, pivotIndex - 1);
        // Quicksort all the elements above the pivot
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Rearranges the subarray between indices [low] and [high]
// by putting a selected pivot element in its correct index.
// Returns the pivot's index.
int partition(int arr[], int low, int high) {
    // Pick a pivot (last element of subarray)
    int pivot = arr[high];

    // i is upper index of subarray of all values <= pivot
    int i = low - 1;
    // for each element between low and high
    for (int j = low; j < high; j++) {
        // if current element <= pivot 
        if (arr[j] <= pivot) {
            // increment i
            i = i + 1;
            // swap elements at i and j
            swap(arr[i], arr[j]);
        }
    }
    // place pivot at end of i region and return its index
    swap (arr[i + 1], arr[high]);
    return i + 1;
}
```
#### Why it works
The *partition* function sorts the array into three subarrays:
* everything less than the pivot
* the pivot
* everything greater than the pivot

In other words, the partition function puts the pivot in its proper 
spot in the array. The Quicksort function then calls Quicksort on the
two subarrays it creates.

#### Time Complexity
$T(n) = O(n) + 2T({n-1 \over 2})$

$O(n \cdot lg(n))$ by the Master theorem

#### Use Cases
It is a fast sorting algorithm. Not stable, though.

## Counting Sort
#### Tweet Summary
Counts how many element of each value are in the array, then 
reassembles accordingly.

#### Pseudocode
```python
def countingSort(A):
    counts = [0] * max(A)
    
    # count values
    for val in A:
        counts[val] += 1
    
    # accumulate them for stability's sake
    for i in range(1, len(counts))
        counts[i] += counts[i - 1]

    # traverse array in reverse to maintain stability
    output = [0] * len(A)
    for i in range(len(A) - 1, -1, -1):
        output[counts[A[i]] - 1] = A[i]
        counts[A[i]] -= 1

    # copy over into original array
    for i in range(len(A)):
        A[i] = output[i]
```

#### Why it works
It abuses space in order to sort the array without any comparisons.

#### Time Complexity
$O(n+k)$, where $k$ is the range of the input.

#### Use Cases
When your data is in a small range. Otherwise, it has a very long 
array to traverse.

## Radix Sort
#### Tweet Summary
It uses a linear time sorting algorithm (like counting sort) to sort 
the array based on digits, starting from the least significant to the 
most significant. It looks like magic.

#### Pseudocode
```python
def RadixSort(arr):
    # Step 1: Find the maximum number to know the number of digits
    max_element = max(arr)

    # Step 2: Initialize exp to 1 (for the least significant digit)
    exp = 1

    # Step 3: Perform Counting Sort for every digit
    while (max_element // exp) > 0:
        CountingSortByDigit(arr, exp)
        exp = exp * 10  # Move to the next more significant digit
```

#### Why it works
Bro idk

#### Time Complexity
$O(n \cdot d)$, where $d$ is the number of digits of the maximum 
element.

#### Use Cases
Good for:
* integers, strings, dates and other forms of data that have a "most 
  significant" and "least significant" place
* when the number of digits is relatively small
* stable sorting

Bad for:
* floating point digits
* when you're tight on space (underlying sorting algo abuses space)

## Heaps
Near-complete binary trees that maintain a min- or max-heap property:
**The parents are always greater (in max-heap) or less (in min-heap) 
than the children.**

### ReheapDown
#### Tweet Summary
If the specified node is smaller than its child(ren), swap it with 
its greatest child, then recurse down.

#### Pseudocode
```python
def reheapDown(arr, n, i):
    # Initialize largest as root
    largest = i
    left = 2 * i + 1     # Left child index
    right = 2 * i + 2    # Right child index

    # If left child exists and is greater than root
    if left < n and arr[left] > arr[largest]:
        largest = left

    # If right child exists and is greater than current largest
    if right < n and arr[right] > arr[largest]:
        largest = right

    # If largest is not root, swap and continue heapifying
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # Swap

        # Recursively heapify the affected subtree
        reheapDown(arr, n, largest)
```
#### Time complexity
$O(lg(n))$, or $O(h)$, where $h$ is the height of the heap.

### ReheapUp
#### Tweet Summary
While the node is larger than its parent, swap it with its parent.
#### Pseudocode
```python
def reheapUp(arr, i):
    parent = (i - 1) // 2
    while(parent >= 0 and arr[parent] < arr[i]):
        swap(arr[parent], arr[i])
        i = parent
        parent = (i - 1) // 2
```

### Heapify
#### Pseudocode
```python
def heapify(arr, n):
    for i in range(n, 0, -1):
        reheapDown(arr, n, i)
```

### Insert
#### Tweet Summary
Insert the node at the bottom, then bubble it up.

#### Pseudocode
```python
def insert(arr, n, i):
    arr[n] = i

    reheapUp(arr, n)
```

### Update
#### Tweet Summary
Update the value of the node. If it's larger than the original value, 
reheap-up. If it's smaller, reheap-down

#### Pseudocode
```python
def update(arr, n, i, x):
    original = arr[i]
    arr[i] = x
    if x > original:
        reheapUp(arr, i)
    if x < original:
        reheapDown(arr, n, i)
```

### Delete
#### Tweet Summary
Update the node to be deleted with the bottommost node

#### Pseudocode
```python
def delete(arr, n, i):
    update(arr, n, i, arr[n])
```

### HeapSort
#### Tweet Summary
Build a max heap, then repeatedly pop the top off, reheaping each 
iteration, until there's nothing left to pop.

#### Pseudocode
```python
def heap_sort(arr):
    n = len(arr)

    # Build a maxheap: call heapify for all non-leaf nodes
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extract elements one by one from the heap
    for i in range(n - 1, 0, -1):
        # Move current root (largest) to end
        arr[i], arr[0] = arr[0], arr[i]

        # Call heapify on the reduced heap
        reheapDown(arr, i, 0)
```

#### Why it works
It's pretty straightforward

#### Time Complexity
$O(n \cdot lg(n))$

#### Use Cases
* not worried about stability
* predictable time complexity (doesn't stray too far from 
  $O(n \cdot lg(n))$)
* Heaps themselves are good
## Binary Search Trees
### Insert Into BST
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
### Deletion From BST
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Red-Black Trees
Self-balancing trees that use colors to balance.
* Nodes are either red or black
* Leaves (null nodes) are black
* Red nodes have black children
  * As a corollary, never two consecutive red nodes
* For each node, each path to every leaf has the *same number of **black** 
nodes* (i.e. black-height is the same)

**Black-height**: number of black nodes from a node to a leaf 
(including the NIL leaf), not counting itself.

**A red-black tree with $n$ internal nodes has a height at most $2lg(n+1)$**
### Left and Right Rotate
For left rotation, right child of `x` (`y`) is not null

For right rotation, left child of `x` (`y`) is not null
#### Pseudocode
```python
def leftRotate(self, x):
    y = x.left
    x.right = y.left
    if y.left != None:
        y.left.parent = x
    y.parent = x.parent
    if x.parent == None:
        self.root = y
    elif x == x.parent.left:
        x.parent.left = y
    else:
        x.parent.right = y
    y.left = x
    x.parent = y

def rightRotate(self, x):
    y = x.right
    x.left = y.right
    if y.right != None:
        y.right.parent = x
    y.parent = x.parent
    if x.parent == None:
        self.root = y
    elif x == x.parent.right:
        x.parent.right = y
    else:
        x.parent.left = y
    y.right = x
    x.parent = y
```
### Insert
Insert into tree as if it's a normal BST.

Color the node red.

Resolve RB tree property conflicts.
#### Pseudocode
```python
def insert(self, z):
    x = self.root
    # Traverse down the tree
    while True:
        if z < x:
            if x.left == None:
                break
            x = x.left
        else:
            if x.left == None:
                break
            x = x.right
    # X is the node whose child you want to make Z
    if z < x:
        x.left = z
    else:
        x.right = z
    z.parent = x
    z.color = red
    insertFixup(z)

```
### Insert Fixup
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
### Update
### Delete
### Insert
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Hash Table
### Insert with Linear Probing
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
### Insert with Double Hashing (choose your own hash functions)
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Knapsack Algorithm (Dynamic Programming)
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Greedy Interval Scheduling
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Breadth-First Search of a Graph
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Depth-First Search of a Tree
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Topological Sort
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Finding Strongly Connected Components
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Prims Algorithm
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Kruskal's Algo
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Prove that the VERTEX-COVER problem reduces to SET-COVER problem
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
## Prove that the SET-COVER problem reduces to VERTEX-COVER problem
#### Tweet Summary
#### Pseudocode
#### Why it works
#### Time Complexity
#### Use Cases
