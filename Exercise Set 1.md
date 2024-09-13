# Exercise Set 1

## 1.4
> Write an algo that takes an array A of n integers and returns the sum of all
 elements in the array.  Then, determine the WCRT in big-O notation via a 
 line-by-line analysis.  Do you think there is a faster algo that sums all elements 
 in an array?  Why or why not?

```
Sum(A):
    sum = 0                     // O(1)
    for i=0 to length(A) - 1:   // O(n)
        sum = sum + A[i]        // O(1)
    return sum                  // O(1)

// 1 + n*1 + 1 = 2 + n = O(n)
```
The WCRT is O(n), since it has to iterate through each value of the array in order
to find the sum. There cannot be a faster algorithm because there is no way to avoid 
touching each element at least once.

## 1.5
Run [this file](merge_sort.py).

Output:
```
Given list:  [1, 2, 7, 3, 5, 6, 9, 8, 10]
Sorted list:  [1, 2, 3, 5, 6, 7, 8, 9, 10]

Given list:  [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Sorted list:  [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

Given list:  [4, 3, 4, 3, 4, 3, 8, 11, 3, 0, 2, 2, 3, 2, 0]
Sorted list:  [0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 8, 11]

Given list:  [9, -2, 5, 12, -3.14, 7, 1.922, 0, -0.6]
Sorted list:  [-3.14, -2, -0.6, 0, 1.922, 5, 7, 9, 12]
```

## 1.6
> Prove that the WCRT of the Bubble Sort algorithm is O(n^2), by a careful 
line-by-line analysis and exact calculation of number of steps executed, and, of 
course, the definition of Big-O.  You will need the formula for the sum of the first 
n integers (look it up).

```
bubbleSort(A, n):
    for i = n-1 to 0:                       // O(n)
        for j = 1 to i:                     // O(i)
            if (A[j-1] > A[j])              // O(1)
                A[j-1], A[j] = A[j], A[j-1] // O(1)
```
### Proof:
1. The outer `for` loop runs `n` times
2. The inner `for` loop runs `i` times, where `i` is the decrementing 
value of the outer `for` loop
3. That means on the first pass of outer loop, the inner loop will run 
`n` times. On the second pass, the inner loop will run `n-1` times, 
and so on until `i` is 0. It looks a little something like this:
```
1 2 3 ... n-1 n
1 2 3 ... n-1
...
1 2 3
1 2
1
```
4. The number of passes can be expressed as the area of this 
triangular diagram, which is `n * n / 2`, or `(n^2)/2`
5. In Big-O notation, we drop constants, so the WCRT of the Bubble 
Sort Algorithm is `O(n^2)`

## 1.7
> Use the master method to give tight asymptotic bounds for the following 
recurrences.

### a. `T(n) = 2T(n/4) + 1`

`a = 2`, `b = 4`, `d = 0`

`4^0 = 1`, so `a > b^d`

`log_4(2) = 0.5`

Therefore, the time complexity is `O(n^0.5)`, or `O(sqrt(n))`

### b. `T(n) = 2T(n/4) + sqrt(n)`

`a = 2`, `b = 4`, `d = 0.5`

`4^0.5 = 2`, so `a = b^d`

Therefore, the time complexity is `O(sqrt(n) * log(n))`

### c. `T(n) = 2T(n/4) + sqrt(n)lg^2(n)`

The master method does not work to give tight asymptotic bounds to this
recurrence because the term `sqrt(n)lg^2(n)` cannot be re-written as a
power of `n`.

A loose asymptotic bound may be found by setting the second term to a
power of `n` greater than `sqrt(n)lg^2(n)` for any arbitrarily large
`n`. For example, it could be `n`. In that case,

`a = 2`, `b = 4`, `d = 1`

`4^1 = 4`, so `a < b^d`

Therefore, a loose estimation for the time complexity is `O(n)`

### d. `T(n) = 2T(n/4) + n`

`a = 2`, `b = 4`, `d = 1`

`4^1 = 4`, so `a < b^d`

Therefore, the time complexity is `O(n)`

### e. `T(n) = 2T(n/4) + n^2`

`a = 2`, `b = 4`, `d = 2`

`4^2 = 4`, so `a < b^d`

Therefore, the time complexity is `O(n^2)`

## 1.8
> Use the Master Theorem to find the WCRT in Big-O notation of the Binary Search 
algorithm of a sorted array.  You may use ChatGPT or other resources to describe or 
write the algorithm for you, but you must provide a recursive time complexity 
formula by analyzing the algo by hand (considering the time complexity of each 
recursive call, how many subproblems are getting solved, how the array’s getting 
split, etc. ) and use the Master Theorem to find a closed formula big-O notation 
final WCRT.  Please include this work in your submission. P.S. it will be painfully 
easy to tell if ChatGPT solved the whole problem for you.  Don’t try it.

```
function binarySearch(array, target, low, high):            // T(n)
    if low > high:                                          // O(1)
        # base case: target not found
        return -1
    
    mid = floor((low + high) / 2)                           // O(1)
    
    if array[mid] == target:                                // O(1)
        # target found at index mid
        return mid                                          // O(1)
    
    else if array[mid] < target:                            // O(1)
        # search in the right half
        return binarySearch(array, target, mid + 1, high)   // T(n/2)
    
    else:
        # search in the left half
        return binarySearch(array, target, low, mid - 1)    // T(n/2)
```

```
T(n) = O(1)             if array[mid] == target, or if n = 1
     = O(1) + T(n/2)    if array[mid] != target
```
By the Master Theorem, `a = 1`, `b = 2`, `d = 0`.

`2^0 = 1`, so `a = b^d`.

Therefore, the time complexity is `O(lg(n))`.

## 1.9
> Use repeated substitution to find the WCRT of Binary Search in Big-O 
notation.  Additionally, prove using induction that your closed 
formula is correct.

```
T(n) = O(1)             if array[mid] == target, or if n = 1
     = O(1) + T(n/2)    if array[mid] != target
```
`T(n) = 1 + T(n/2)`

`T(n) = 1 + (1 + T(n/4))`

`T(n) = 2 + T(n/(2^2))`

`T(n) = 3 + T(n/(2^3))`

`T(n) = m + T(n/(2^m))` for some `m`

We know that `T(n) = O(1)` when `n = 1`. The worst case scenario of 
this algorithm is that it must divide the array all the way until it's 
left with a one-element subarray, so we can set `n/(2^m) = 1`. Solving 
for m, we get `n = 2^m`, so `m = lg(n)`. We can substitute that into the previous equation to get:

`T(n) = lg(n) + 1`, which means `T(n) = O(lg(n))`.

***How to prove using induction that my closed formula is correct???***

## 1.10
> Professor Caesar wants to develop a matrix-multiplication algorithm 
that uses a divide and conquer approach, diving each matrix into n/4x 
n/4 submatrices, with the divide and combine steps together taking O
(n^2 ).  Suppose that the professor's algo creates two recursive 
subproblems of size n/4.  What is the WCRT of Caesar’s algo?  Please 
show your work.

```
T(n) = 1                // base case
     = 2T(n/4) + n^2    // recursive case
```
Using the Master theorem:

`a = 2`, `b = 4`, `d = 2`

`4^2 = 16`, so `a < b^d`

So `T(n) = O(n^2)`

## Bonus Exercise 1.1
> Complete exercise 2-2 (all parts) on page 46 of the textbook (should 
be the problem analyzing Bubble Sort).

```
BUBBLESORT(A, n)
1   for i = 1 to n-1
2       for j = n downto i + 1
3           if A[j] < A[j - 1]
4               exchange A[j] with A[j - 1]
```

### a. 
> Let A' denote the array A after BUBBLESORT(A, n) is executed. To 
prove that BUBBLESORT is correct, you need to prove that it terminates 
and that `A'[1] <= A'[2] <= ... <= A'[n]`. In order to show that 
BUBBLESORT actually sorts, what else do you need to prove?

You also need to prove that no elements are added or removed between 
`A` and `A'`, and that `A'` is the same length as `A`
- For instance, if `A = [3, 1, 4, 1, 5]`, and 
`A' = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]`, that would still technically 
not violate the rules outlined above, but the algorithm would not work 
properly.

### b.
> State precisely a loop invariant for the **for** loop in lines 
2-4, and prove that this loop invariant holds. Your proof should use 
the structure of the loop-invariant proof presented in this chapter

The inner **for** loop moves the smallest element of the unsorted 
subarray down to the end of  the sorted subarray. For iteration `i`, 
assume that there is a portion of the array at the beginning with 
`i - 1` elements that are already in sorted order. The inner **for** 
loop brings the smallest element of the unsorted subarray down into 
the end of the sorted subarray, thereby increasing the sorted 
portion's size by 1. The inner **for** loop terminates when `j` 
reaches `i + 1`, that is, when it checks and swaps the elements at 
indices `i` and `i + 1`. This works because all the elements in the 
unsorted subarray are equal to or greater than all the elements in the 
sorted subarray.

### c.
> Using the termination condition of the loop invariant proved in part 
(b), state a loop invariant for the for loop in lines 1-4 that allows 
you to prove inequality (2.5). Your proof should use the structure of 
the loop-invariant proof presented in this chapter.

Before the loop begins, everything from index `0` to `i` is already
sorted. After the loop ends, everything from index `0` to `i + 1` is
sorted. As `i` increases, the sorted portion of the array grows until
it reaches `n - 1`. The element at index `n` is the greatest element
in the array, because of the inner loop invariant's termination
condition. When the sorted portion of the array is `n - 1`, the array 
is fully sorted, and the outer **for** loop terminates.

### d.
> What is the worst-case running time of BUBBLESORT? How does it 
compare with the running time of INSERTION-SORT?

Both BUBBLESORT and INSERTION-SORT have a WCRT at `O(n^2)`, though a 
quick Google search says that INSERTION-SORT tends to be faster in 
practice because it makes fewer swaps.