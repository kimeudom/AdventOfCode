// Searching and finding tools for this challenge

#include <iostream>
#include <string.h>

using namespace std;
void merge(int array[], int start, int median, int end) {
  // The counters for the function
  int i, j, k;
  // Gettin the size of the left and right arrays
  int sizeOfLeft = median - start + 1;
  int sizeOfRight = end - median;

  // Creaeting temporary arrays to hold the left and right sub arrays
  int leftArray[sizeOfLeft];
  int rightArray[sizeOfRight];

  // Copying the main array into the sub arrays
  for (i = 0; i < sizeOfLeft; i++) {
    leftArray[i] = array[start + i];
  }
  for (j = 0; j < sizeOfRight; j++) {
    rightArray[j] = array[median + j + 1];
  }

  // Merging the arrays
  i = 0;
  j = 0;
  k = start;

  while (i < sizeOfLeft && j < sizeOfRight) {
    if (leftArray[i] <= rightArray[j]) {
      array[k] = leftArray[i];
      i++;
    } else {
      array[k] = rightArray[j];
      j++;
    }
    k++;
  }

  // Fill the remainder of the sub arrays
  while (i < sizeOfLeft) {
    array[k] = leftArray[i];
    i++;
    k++;
  }
  while (j < sizeOfRight) {
    array[k] = rightArray[j];
    j++;
    k++;
  }
}

void mergeSort(int array[], int start, int end) {
  if (end > start) {
    // The middle of an array passed to the function
    int median = start + (end - start) / 2;

    // Sort the left
    mergeSort(array, start, median);
    // Sort the right
    mergeSort(array, median + 1, end);

    merge(array, start, median, end);
  }
}

// Recursive binary Search
// parameters, integer array, lowest index, highest index, search parameter
// (key)
int binarySearch(int arr[], int low, int high, int key) {
  while (high >= low) {
    int mid = low + (high - low) / 2;

    // Return the mid index if the key is present in the middlej
    if (arr[mid] == key) {
      return mid;
    }

    if (arr[mid] > key) {
      return binarySearch(arr, low, mid - 1, key); // Left binary search
    }
    return binarySearch(arr, mid + 1, high, key); // Right binary search
  }

  return -1;
}

string intArrToString(int *array, int items) {
  string s;
  for (int i = 0; i < items; i++) {
    s.push_back(array[i]);
  }
  return s;
}

int *stringToIntArray(string s) {

  int stringSize = s.length();
  int *a = (int *)malloc(sizeof(int) * stringSize);

  for (int i = 0; i < stringSize; i++) {
    a[i] = s[i];
  }

  return a;
}

void swapValues(int *a, int *b) {
  double temp;
  temp = *b;
  *b = *a;
  *a = temp;
}

// Sorting the array
void quicksort(int array[], int start, int end) {
  if (end > start) {
    // taking the median index as the pivot

    int median = (int)(start + end) / 2;
    double referenceValue = array[median];
    // Make the median value the end value

    swapValues(&array[median],
               &array[end]); // Moving the median value to the end and adding it
                             // at its indexed postion later
    int indexOfSortedMedian =
        start - 1; // initial proposed position of the median value in the worst
                   // case of selection in the left direction
    for (int i = start; i < end; i++) {
      if (array[i] < array[end]) {
        indexOfSortedMedian++; // Move up one index when a less than value is
                               // found
        swapValues(&array[i], &array[indexOfSortedMedian]);
      }
    }
    indexOfSortedMedian++; // Setting the median index one up the previous to be
                           // after its last moved value
    swapValues(&array[end], &array[indexOfSortedMedian]);

    // perform quick sort on the upper and lower sub arrays
    quicksort(array, start, indexOfSortedMedian - 1); // Below
    quicksort(array, indexOfSortedMedian + 1, end);   // Above
  }
}
