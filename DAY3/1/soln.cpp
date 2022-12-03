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
  } else { // uppercase letter 65 - 90 + 26 (Upper case values start at 27)
    value = c - 64 + 26;
  }

  return value;
}

// Linear search two string for a similar character
char findSharedItem(string left, string right) {
  char c = 0;
  for (int i = 0; i < left.length(); i++) {
    for (int j = 0; j < right.length(); j++) {
      if (left[i] == right[j]) {
        return left[i];
      }
    }
  }
  // Return null character if no shared item exists
  return c;
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

  string line;
  int totalPoints = 0;
  while (input.peek() != EOF) {
    getline(input, line, '\n');
    string left;
    string right;
    int median = (line.length() / 2 - 1);

    // Dividing the string into two

    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      if (i <= median) {
        left.push_back(c);
      } else {
        right.push_back(c);
      }
    }

    char c = findSharedItem(left, right);
  }

  cout << totalPoints << endl;
  return 0;
}
