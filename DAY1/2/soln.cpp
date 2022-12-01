#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// A linked list structure to store the running total of calories
class Node {
public:
  int value;
  Node *next;
};

Node *head = NULL;

int getSize() {
  Node *temp;
  temp = head;
  int i = 0;

  // Iterate through the list untill we find the largest sum
  while (temp != NULL) {
    temp = temp->next;
    i++;
  }

  return i;
}

void addToList(int groupTotal) {
  Node *temp = new Node();
  temp->value = groupTotal;
  temp->next = NULL;

  temp->next = head;
  head = temp;
}

void addGrptotal(string filepath) {

  // Opening the file path
  ifstream input;
  input.open(filepath);

  // Check for errors while opening
  if (input.fail()) {
    cerr << "Could not open file" << endl;
    return;
  }

  // Identifying group totals
  int grouptotal = 0;
  while (input.peek() != EOF) {
    string line;
    getline(input, line, '\n');

    if (line != "") {
      grouptotal += stoi(line);
    } else {
      addToList(grouptotal);
      grouptotal = 0;
    }
  }

  // Add the last group
  if (input.peek() == EOF) {
    addToList(grouptotal);
  }

  input.close();
}

// Adding the linked list to an array
void addToArray(int array[]) {
  Node *temp = head;
  int i = 0;
  while (temp->next != NULL) {
    array[i] = temp->value;
    temp = temp->next;
    i++;
  }
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

int main(int argc, char **argv) {

  // Check input args
  if (argc < 2) {
    cerr << "Usage: ./soln <<input file path>>" << endl;
    return -1;
  }

  string filepath = argv[1];
  addGrptotal(filepath);

  int linkedListSize = getSize();
  int totals[linkedListSize];
  addToArray(totals);
  quicksort(totals, 0, linkedListSize - 1);

  // Invert the array
  unsigned int i, j;
  for (i = 0, j = linkedListSize - 1; i < j; i++, j--) {
    int t;
    t = totals[j];
    totals[j] = totals[i];
    totals[i] = t;
  }

  int top3 = totals[0] + totals[1] + totals[2];
  std::cout << top3 << endl;
}
