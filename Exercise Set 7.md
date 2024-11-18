# Exercise Set 9, Module 9 - Greedy Algorithms

## 2. Activity Selection Problem
```python
# Jonah Ebent, 11/15/24
#   You are given a set of activities, each with a start time
# and an end time (integers in 24hr time). Your goal is to
# select the maximum number of non-overlapping activities
# that can be scheduled. In other words, you want to find the
# largest subset of activities that don't conflict with each
# other in terms of their time intervals.
import random

def create_activities(n, max=24):
    '''returns a list of size `n` of intervals between 1 and 24, inclusive'''
    activities = []
    for _ in range(n):
        s = random.randint(1, max - 1)
        f = random.randint(s + 1, max)
        activities.append((s, f))
    return sort_activities(activities)

def sort_activities(activities: list):
    '''returns the activities sorted using radix sort so that
    activities with the same start time are sorted by their end time'''
    return sorted(sorted(activities, key = lambda x: x[1]), key = lambda x: x[0])

def schedule_activities(activities: list):
    '''returns the largest set of non-conflicting activities'''
    schedule = []
    while len(activities) > 0:
        i = min(activities, key=lambda x: x[1])
        schedule.append(i)
        activities = [x for x in activities if compatible(i, x)]    
    return schedule

def compatible(a, b):
    '''returns true if two intervals are compatible (not overlapping)'''
    [a, b] = sort_activities([a, b])
    return a[0] != b[0] and a[1] <= b[0]
    
if __name__ == "__main__":
    activities = [
        (1, 3),
        (2, 5),
        (3, 8),
        (6, 7),
        (8, 10),
        (9, 12)
    ]
    print(schedule_activities(activities))  # [(1, 3), (6, 7), (8, 10)]
```

## 3. Choosing Greed - File Merge Problem
```python
# Jonah Ebent, 11/16/24

import heapq
import random

def merge_files(files: list):
    '''Returns the cost of an optimal way to merge multiple files,
    given a list of their sizes. It uses a greedy algorithm which
    repeatedly merges the two smallest items. The greedy algorithm
    works because smaller file sizes contribute less to the total
    cost when repeatedly added in subsequent merges.
    
    Rules:
    - You can only merge two files at the same time
    - The cost of each merge is the sum of the sizes of the two files.
    
    Complexity: It is implemented using priority queue, giving it a
    time complexity of `O(n lg(n))`.'''

    if len(files) == 0:
        return 0
    heapq.heapify(files)            # heapify the list of files
    while len(files) > 1:
        a = heapq.heappop(files)    # merge two smallest files
        b = heapq.heappop(files)
        heapq.heappush(files, a+b)  # push result onto heap
    return files[0]


def generate_files(n, max = 20):
    '''Helper function to generate a list of file sizes.'''
    return [random.randint(1,max) for _ in range(n)]
```

## 4. When Greed is Good
> When is a greedy approach optimal (or even possible) for solving 
> a problem?  What are the key differences between a problem that 
> can solved using a dynamic programming approach and that which
> can be solved using a greedy approach?

A greedy approach is optimal/possible for solving a problem when it
has two properties:
1. **Optimal Subproblems**: the optimal solutions to the subproblems
   build up to the problem's solution
2. **Greedy Property**: an global optimal solution can be found by
   choosing optimal solutions at each step without concern for future
   consequences

The key differences between problems that can be solved greedily versus
dynamically are:
- **Overlapping Subproblems**: problems solved using dynamic programming
  typically have overlapping subproblems, whereas problems with greedy
  solutions typically have non-overlapping subproblems
- **Memoization**: because dynamic programming typically has overlapping
  subproblems, it makes use of memoization to reduce computation time, but
  greedy algorithms do not memoize because they do not have overlapping
  subproblems
- **Greedy Property**: greedy problems exhibit the greedy property described
  above, whereas dynamic programming problems do not

Examples:
* **0/1 Knapsack Problem (Dynamic Programming)**: this problem must be solved
  using dynamic programming because it does not satisfy the greedy property.
  The optimal decision in one subproblem depends on the optimal decisions made
  in smaller subproblems.
* **Fractional Knapsack Problem (Greedy Algorithms)**: this problem can be
  solved greedily because it satisfies the greedy property. The optimal decision
  in one subproblem does not depend on the optimal decisions made in subsequent
  subproblems.