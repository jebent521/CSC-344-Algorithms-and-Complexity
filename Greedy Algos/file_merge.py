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