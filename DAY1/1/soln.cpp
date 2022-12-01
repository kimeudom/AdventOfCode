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

int getMax() {
  Node *temp;
  temp = head;
  int max = 0;

  // Iterate through the list untill we find the largest sum
  while (temp != NULL) {
    if (temp->value > max) {
      max = temp->value;
    }
    temp = temp->next;
  }

  return max;
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

int main(int argc, char **argv) {

  // Check input args
  if (argc < 2) {
    cerr << "Usage: ./soln <<input file path>>" << endl;
    return -1;
  }

  Node *HEAD = NULL;

  string filepath = argv[1];
  addGrptotal(filepath);
  cout << getMax() << endl;

  return 0;
}
