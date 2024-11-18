# Jonah Ebent, 11/15/24
#   Write a program in any language that takes a list of ten objects
# and their respective associated weights and values, along with a
# maximum capacity for your knapsack, and returns a list of items
# you will take, how much of each item you take, and the total value
# of everything in your knapsack.

import random

def fractional_knapsack(
        max_weight: int,
        values: list[int],
        weights: list[int]
    ) -> tuple[int, list[(int, float)]]:
    '''solves the fractional knapsack problem, returning a tuple of the max value and a list of the selected indices and fractions'''
    # create a list of tuples, representing items: (index, value, weight)
    items = sorted(list(zip(
            range(len(weights)),
            values,
            weights,
            # enforce weights and values are same length
            strict=True
        )),
        # sort by ratio of value to weight
        key = lambda i: i[1] / i[2]
    )
    # initialize return values
    total_value = 0
    sack = []
    # grab item with greatest value:weight ratio until bag is full or ALDI is empty
    while max_weight > 0 and len(items) > 0:
        i, v, w = items.pop()
        # if item's weight is less than max, take the entire thing
        # otherwise, take only a fraction of the item
        fraction = 1 if w <= max_weight else max_weight / w
        # stuff it in the sack
        sack.append((i, fraction))
        total_value += v * fraction
        max_weight -= w * fraction
    return total_value, sack

def rand_list(n):
    '''return a list of length `n`, with random integers between 1 and 9, inclusive'''
    return [random.randint(1, 9) for _ in range(n)]