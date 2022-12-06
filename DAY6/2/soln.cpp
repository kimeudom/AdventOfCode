#include <fstream>
#include <iostream>
#include <set>

using namespace std;
int checkConcurrency(string line) {

  for (int i = 0; i < line.length() - 3; i++) {
    char a, b, c, d;
    set<char> s;
    a = line[i];
    b = line[i + 1];
    c = line[i + 2];
    d = line[i + 3];
    s.insert(a);
    s.insert(b);
    s.insert(c);
    s.insert(d);

    if (s.size() == 4) {
      return i + 1 + 3;
    }
    s.clear();
  }

  return -1;
}

int checkMessage(string line) {

  for (int i = 0; i < line.length() - 13; i++) {
    set<char> s;
    for (int j = 0; j < 14; j++) {
      s.insert(line[i + j]);
    }

    if (s.size() == 14) {
      return i + 1 + 13;
    }
    s.clear();
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

  getline(input, line);
  int startOfMessage = checkMessage(line);
  cout << startOfMessage << endl;
  input.close();
}