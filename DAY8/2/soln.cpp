#include <fstream>
#include <iostream>

using namespace std;

int checkVisibleDistance(int arr[][99], int i, int j, char Direction) {
  int counter = 0;
  if (i == 0 || j == 0 || j == 99 - 1 || i == 99 - 1 || arr[i][j] == 0) {
    return counter;
  }

  switch (Direction) {
  case 'N':
    for (int k = i - 1; k >= 0; k--) {
      counter++;
      if (arr[i][j] <= arr[k][j]) {
        break;
      }
    }
    break;
  case 'S':
    for (int k = i + 1; k < 99; k++) {
      counter++;
      if (arr[i][j] <= arr[k][j]) {
        break;
      }
    }
    break;
  case 'E':
    for (int k = j - 1; k >= 0; k--) {
      counter++;
      if (arr[i][j] <= arr[i][k]) {
        break;
      }
    }
    break;
  case 'W':
    for (int k = j + 1; k < 99; k++) {
      counter++;
      if (arr[i][j] <= arr[i][k]) {
        break;
      }
    }
    break;
  }

  return counter;
}

void getScenicScore(int arr[][99], int SIZE, int store[][99]) {
  int score;

  // Check NSEW upto the blocking tree
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Check NSEW
      int N, S, E, W;
      N = checkVisibleDistance(arr, i, j, 'N');
      S = checkVisibleDistance(arr, i, j, 'S');
      E = checkVisibleDistance(arr, i, j, 'E');
      W = checkVisibleDistance(arr, i, j, 'W');

      score = N * S * E * W;
      store[i][j] = score;
    }
  }
}

int getMax(int arr[][99], int SIZE) {
  int max = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (arr[i][j] > max) {
        max = arr[i][j];
      }
    }
  }
  return max;
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
  int store[99][99];
  int i = 0;

  while (input.peek() != EOF) {
    getline(input, line);
    for (int j = 0; j < SIZE; j++) {
      arr[i][j] = line[j] - '0';
    }
    i++;
  }

  input.close();

  // Get Scenic values
  getScenicScore(arr, SIZE, store);

  cout << getMax(store, SIZE) << endl;
  return 0;
}