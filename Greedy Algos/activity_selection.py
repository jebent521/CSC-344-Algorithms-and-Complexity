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