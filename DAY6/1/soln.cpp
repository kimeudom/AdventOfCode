#include <fstream>
#include <iostream>

using namespace std;

// Checks the edge between lines if there exists the "start packet marker"
// Returns -1 if there is no concurrency
int edgeConcurrency(int lineCount, string edge6) {
  for (int i = 0; edge6.length() - 3; i++) {
    if (edge6[i] != edge6[i + 1] != edge6[i + 2] != edge6[i + 3]) {
      if (i > 3) {
        return (lineCount * 4095) + 4095 + i + 1;
      } else {
        return (lineCount * 4095) + (4095 - 3) + i + 1;
      }
      return i;
    }
  }

  // Returns -1 if there is no edge concurrency
  return -1;
}

// Checks an input line if there exists the "start packet marker"
// Returns -1 if there is no concurrency
int checkConcurrency(int lineCount, string line) {
  for (int i = 0; i < line.length() - 3; i++) {
    if (line[1] != line[i + 1] != line[i + 2] != line[i + 3]) {
      // Return the sum of line characters above plus the line index plus one to
      // escape array indexing to normal indexing
      return (lineCount * 4095) + i + 1;
    }
  }

  // Return -1 if there is no concurrency in the line
  return -1;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage :: ./soln <<puzzle input>>" << endl;
    return -1;
  }

  // Open the file
  string filepath = argv[1];
  ifstream input;
  input.open(filepath);

  if (input.fail()) {
    cerr << "Could not open the file" << endl;
    return -2;
  }

  // Store the line

  string line;
  int lineCount = 0;
  string last3;
  while (input.peek() != EOF) {

    getline(input, line, '\n');
    // Check for edge concurrency

    if (line.length() == 4095) {
      if (lineCount > 0) {
        // Check last 3 if line count > 0
        string edge6 = last3 + line.substr(4091, 4094);
        if (edgeConcurrency(lineCount, edge6) != -1) {
          cout << edgeConcurrency(lineCount, edge6);
          return 0;
        }
      }

      // If no edge concurrency, then check for line concurrency
      if (checkConcurrency(lineCount, line)) {
        cout << checkConcurrency(lineCount, line);
        return 0;
      }

      // Reinitialize the counters
      lineCount++;
      last3 = line.substr(line.length() - 3, line.length() - 1);
    }

    // If the line length is not 4095, then we are at the last line

    if (lineCount > 0) {
      string edge6 = last3 + line.substr(line.length() - 3, line.length() - 1);
      if (edgeConcurrency(lineCount, edge6)) {
        cout << edgeConcurrency(lineCount, edge6) << endl;
        return 0;
      }

      // Check line concurrency
      if (checkConcurrency(lineCount, line)) {
        cout << checkConcurrency(lineCount, line) << endl;
        return 0;
      }
    }
  }

  return 0;
}