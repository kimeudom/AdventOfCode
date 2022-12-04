#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool fullyContain(string a, string b) {
  int aLow, aHigh, bLow, bHigh;
  // Convert the string values to integer values for comparison
  aLow = stoi(a.substr(0, a.find('-')));
  aHigh = stoi(a.substr(a.find('-') + 1, a.length()));
  bLow = stoi(b.substr(0, b.find('-')));
  bHigh = stoi(b.substr(b.find('-') + 1, b.length()));

  // IF a contains b
  if (aLow <= bLow && aHigh >= bHigh) {
    return true;
  }

  // If b contains a
  if (bLow <= aLow && bHigh >= aHigh) {
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

    if (fullyContain(a, b) == true) {
      fullyContainsTotal++;
    }
  }

  cout << fullyContainsTotal << endl;
  return 0;
}