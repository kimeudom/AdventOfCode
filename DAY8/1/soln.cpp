#include <fstream>
#include <iostream>

using namespace std;

bool checkVisible(int arr[][99], int i, int j) {
  bool N = true, S = true, E = true, W = true;
  // Check N
  for (int k = i - 1; k >= 0; k--) {
    if (arr[i][j] <= arr[k][j]) {
      N = false;
      break;
    }
  }
  // Check S
  for (int k = i + 1; k < 99; k++) {
    if (arr[i][j] <= arr[k][j]) {
      S = false;
      break;
    }
  }
  // Check E
  for (int k = j + 1; k < 99; k++) {
    if (arr[i][j] <= arr[i][k]) {
      E = false;
      break;
    }
  }
  // Check W
  for (int k = j - 1; k >= 0; k--) {
    if (arr[i][j] <= arr[i][k]) {
      W = false;
      break;
    }
  }

  if (N || S || E || W) {
    return true;
  }
  return false;
}

int getTreesVisible(int arr[][99], int SIZE) {
  // Those on the perimeter
  int Total = 4 * SIZE - 4;

  // Check NSEW upto the edge
  for (int i = 1; i < SIZE - 1; i++) {
    for (int j = 1; j < SIZE - 1; j++) {
      // Check NSEW
      if (checkVisible(arr, i, j)) {
        Total++;
        continue;
      }
    }
  }
  return Total;
}

int main(int argc, char **argv) {

  if (argc < 2) {
    cerr << "Usage :: ./soln <<puzzle_input>>" << endl;
    return -1;
  }
  string filename = argv[1];
  ifstream input;
  input.open(filename);

  if (input.fail()) {
    cerr << "Could not open file" << endl;
    return -2;
  }

  string line;
  int SIZE = 99;
  int arr[99][99];
  int i = 0;

  while (input.peek() != EOF) {
    getline(input, line);
    for (int j = 0; j < SIZE; j++) {
      arr[i][j] = line[j] - '0';
    }
    i++;
  }

  input.close();
  cout << getTreesVisible(arr, SIZE) << endl;
  return 0;
}