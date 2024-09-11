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

> a. `T(n) = 2T(n/4) + 1`

`a = 2`, `b = 4`, `d = 0`

`4^0 = 1`, so `a > b^d`

`log_4(2) = 0.5`

Therefore, the time complexity is `O(n^0.5)`, or `O(sqrt(n))`

> b. `T(n) = 2T(n/4) + sqrt(n)`

`a = 2`, `b = 4`, `d = 0.5`

`4^0.5 = 2`, so `a = b^d`

Therefore, the time complexity is `O(sqrt(n) * log_4(n))`

> c. `T(n) = 2T(n/4) + sqrt(n)lg^2(n)`

The master method does not work to give tight asymptotic bounds to this
recurrence because the term `sqrt(n)lg^2(n)` cannot be re-written as a
power of `n`.

A loose asymptotic bound may be found by setting the second term to a
power of `n` greater than `sqrt(n)lg^2(n)` for any arbitrarily large
`n`. For example, it could be `n`. In that case,

`a = 2`, `b = 4`, `d = 1`

`4^1 = 4`, so `a < b^d`

Therefore, a loose estimation for the time complexity is `O(n)`

> d. `T(n) = 2T(n/4) + n`

`a = 2`, `b = 4`, `d = 1`

`4^1 = 4`, so `a < b^d`

Therefore, the time complexity is `O(n)`

> e. `T(n) = 2T(n/4) + n^2`

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
T(n) = O(1)             if array[mid] == target
     = O(1) + T(n/2)    if array[mid] != target
```
By the Master Theorem, `a = 1`, `b = 2`, `d = 0`.

`2^0 = 1`, so `a = b^d`.

Therefore, the time complexity is `O(lg(n))`.
