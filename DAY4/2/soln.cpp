#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool anyOverlap(string a, string b) {
  int aLow, aHigh, bLow, bHigh;

  // Convert the string values to integer values for comparison
  aLow = stoi(a.substr(0, a.find('-')));
  aHigh = stoi(a.substr(a.find('-') + 1, a.length()));
  bLow = stoi(b.substr(0, b.find('-')));
  bHigh = stoi(b.substr(b.find('-') + 1, b.length()));

  // Using set theory
  // A set data structure will only store unique elements
  // The sum of elements in the set will be less if duplicate elements
  // are added
  set<int> S;

  // Adding set elements
  // The set data structure does not allow duplicate elements
  for (int i = aLow; i < aHigh + 1; i++) {
    S.insert(i);
  }
  for (int i = bLow; i < bHigh + 1; i++) {
    S.insert(i);
  }

  // If the sum of the set elements isnt equal to the elements in
  // the strings a and b, there is an overlap

  // Total number of expected elements
  int elements = (aHigh - aLow + 1) + (bHigh - bLow + 1);

  if (S.size() < elements) {
    return true;
  }

  return false;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: ./soln <<input path>>" << endl;
    return -1;
  }

  string filepath = argv[1];
  ifstream input;
  input.open(filepath);

  if (input.fail()) {
    cerr << "Could not open file" << endl;
    return -2;
  }

  int fullyContainsTotal = 0;

  while (input.peek() != EOF) {
    // get a pair and split the pairs
    string line;
    string a; // 1st elf
    string b; // 2nd elf

    getline(input, line, '\n');

    // Split the pair into individual designated section areas
    int splitIndex = line.find(',');

    a = line.substr(0, splitIndex);
    b = line.substr(splitIndex + 1, line.length());

    if (anyOverlap(a, b) == true) {
      fullyContainsTotal++;
    }
  }

  cout << fullyContainsTotal << endl;
  return 0;
}