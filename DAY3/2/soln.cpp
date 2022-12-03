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
int findSharedItemIndex(string one, string two, string three) {

  int *arrOne = stringToIntArray(one);
  int *arrTwo = stringToIntArray(two);
  int *arrThree = stringToIntArray(three);

  mergeSort(arrOne, 0, one.length() - 1);
  mergeSort(arrTwo, 0, two.length() - 1);
  mergeSort(arrThree, 0, three.length() - 1);
  int index2;
  int index3;
  for (int i = 0; i < one.length(); i++) {

    index2 = binarySearch(arrTwo, 0, two.length(), arrOne[i]);

    if (index2 != -1) {
      index2 = binarySearch(arrThree, 0, three.length(), arrOne[i]);
      if (index3 != -1) {
        cout << arrOne[i] << "  " << arrTwo[index2] << "  " << arrThree[index3];
      }
    }
  }

  /*
  // Finding the common element
  for (int i = 0; i < one.length(); i++) {
    if (binarySearch(arrTwo, 0, two.length(), arrOne[i]) != -1) {
      if (binarySearch(arrThree, 0, three.length(), arrOne[i]) != -1) {
        char c = arrOne[i];

        cout << "one " << i << " " << c << endl;
        cout << "two " << i << " " << c << endl;
        cout << "three " << i << " " << c << endl;

        return i;
      }
    }
  }

  */

  // else return -1
  return -1;
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

  string lineOne;
  string lineTwo;
  string lineThree;
  int totalPoints = 0;

  while (input.peek() != EOF) {
    // Read three lines at a time
    std::getline(input, lineOne, '\n');
    std::getline(input, lineTwo, '\n');
    std::getline(input, lineThree, '\n');

    char c = lineOne[findSharedItemIndex(lineOne, lineTwo, lineThree)];
    totalPoints += priorityValue(c);

    cout << c << " " << priorityValue(c) << endl;
  }

  std::cout << totalPoints << endl;
  return 0;
}
