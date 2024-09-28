#include <iostream>

using namespace std;

void quicksort(int[], int, int);
int partition(int[], int, int);
void printArray(int[], int);

static void quicksortMain() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    cout << "Unsorted array: ";
    printArray(arr1, 7);
    quicksort(arr1, 0, 6);
    cout << "Sorted array: ";
    printArray(arr1, 7);

    int arr2[] = {9, 8, 7, 6, 5, 3, 1};
    cout << "Unsorted array: ";
    printArray(arr2, 7);
    quicksort(arr2, 0, 6);
    cout << "Sorted array: ";
    printArray(arr2, 7);

    int arr3[] = {9, 1, 5, 2, 6, 2, 1, 1, 1};
    cout << "Unsorted array: ";
    printArray(arr3, 9);
    quicksort(arr3, 0, 8);
    cout << "Sorted array: ";
    printArray(arr3, 9);

    int arr4[] = {5555};
    cout << "Unsorted array: ";
    printArray(arr4, 1);
    quicksort(arr4, 0, 0);
    cout << "Sorted array: ";
    printArray(arr4, 1);
}

// Sorts an array using the quicksort algorithm.
// Initial call: `quicksort(arr, 0, n-1)`, where n is the size of the array
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

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}