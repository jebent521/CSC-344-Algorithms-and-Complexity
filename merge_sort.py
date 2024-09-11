# [1, 2, 7, 3, 5, 6, 9, 8, 10]
# [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
# [4, 3, 4, 3, 4, 3, 8, 11, 3, 0, 2, 2, 3, 2, 0]
# [9, -2, 5, 12, -3.14, 7, 1.922, 0, -0.6]

def main():
    arrays = [
        [1, 2, 7, 3, 5, 6, 9, 8, 10],
        [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
        [4, 3, 4, 3, 4, 3, 8, 11, 3, 0, 2, 2, 3, 2, 0],
        [9, -2, 5, 12, -3.14, 7, 1.922, 0, -0.6],
    ]
    for arr in arrays:
        print("Given list: ", arr)
        merge_sort(arr, 0, len(arr) - 1)
        print("Sorted list: ", arr)
        print()

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

if __name__ == "__main__":
    main()
