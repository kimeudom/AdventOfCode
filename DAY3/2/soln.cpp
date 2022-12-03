#include "tools.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int priorityValue(char c) {
  int value;
  // If there is no shared item
  if (c == 0) {
    return 0;
  }

  // Normalizing the number
  if (c > 90) { // lowercase number 97 - 122
    value = c - 96;
  } else { // uppercase letter 65 - 90
    value = c - 64 + 26;
  }

  return value;
}

void printArray(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl << endl;
}

// Returns the index of the shared item index (in string one) if found in all
// three strings
char findSharedItem(string one, string two, string three) {

  // Converting the string arrays to integer arrays
  // Necesary to implement the search tools in the tools.h header file
  int *arrOne = stringToIntArray(one);
  int *arrTwo = stringToIntArray(two);
  int *arrThree = stringToIntArray(three);

  // Sort the data to use faster searching algorithims
  mergeSort(arrOne, 0, one.length() - 1);
  mergeSort(arrTwo, 0, two.length() - 1);
  mergeSort(arrThree, 0, three.length() - 1);

  // Stores search indexes for line 2 and line 3
  int index2;
  int index3;

  // Iterate through line 1 while checking in lines 2 and 3 for a similar key
  for (int i = 0; i < one.length(); i++) {

    index2 = binarySearch(arrTwo, 0, two.length() - 1, arrOne[i]);

    if (index2 != -1) {
      index3 = binarySearch(arrThree, 0, three.length() - 1, arrOne[i]);
      if (index3 != -1) {
        char c = arrOne[i];
        // Free up memory
        free(arrOne);
        free(arrTwo);
        free(arrThree);

        // return the common element
        return c;
      }
    }
  }

  // else return 0 // Null value
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: ./soln <<puzzle input path>>" << endl;
    return -1;
  }

  string filename = argv[1];
  ifstream input;
  input.open(filename);

  if (input.fail()) {
    cerr << "Failed to open the input file" << endl;
    return -2;
  }

  // Store three lines per one loop as a group
  string lineOne;
  string lineTwo;
  string lineThree;

  int totalPoints = 0;

  while (input.peek() != EOF) {
    // Read three lines at a time
    std::getline(input, lineOne, '\n');
    std::getline(input, lineTwo, '\n');
    std::getline(input, lineThree, '\n');

    // Locate the shared item in the group of three, determine int priority
    // value and add the value to the running total
    char c = findSharedItem(lineOne, lineTwo, lineThree);
    totalPoints += priorityValue(c);
  }

  std::cout << totalPoints << endl;
  return 0;
}
