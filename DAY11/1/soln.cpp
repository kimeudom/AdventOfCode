#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

class List {
private:
  int data;
  List *next;

public:
  List() { data = 0, next = NULL; };
  // Returns the last element pointer value in the list
  List *getLast();
  // Get's the pointer to the first element and dequeue
  List *getFirst();
  // Enqueue the pointer to the end
  // Overloaded for transferring list nodes or making new ones
  void addToEnd(int value);
  void addToEnd(List *ptr);
  // Setters
  void setValue(int value) { data = value; }
  // getters
  int getValue() { return data; }
  List *getNext() { return next; }
};

// Linked List member functions
List *List::getFirst() {
  if (next == NULL) {
    return NULL;
  }

  List *temp = next;
  next = next->next;
  return temp;
}

void List::addToEnd(List *ptr) {
  if (next == NULL) {
    next = ptr;
    return;
  }
  List *last = getLast();
  last->next = ptr;
}

void List::addToEnd(int value) {
  List *temp = new List();
  temp->data = value;

  if (next == NULL) {
    next = temp;
    return;
  }

  List *last = getLast();
  last->next = temp;
}

List *List::getLast() {
  if (next == NULL) {
    return NULL;
  }

  List *temp;
  temp = next;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  return temp;
}

class Monkey {
private:
  List *root;
  int divisor;
  // In order to determine its operation
  int throwTo[2];
  // Index in the list
  int no;

public:
  Monkey(int trueThrow, int falseThrow, int div, int index) {
    root = NULL;
    divisor = div;
    throwTo[0] = trueThrow;
    throwTo[1] = falseThrow;
    no = index;
  }
  // Plays it's turn and returns the index of the monkey to throw to
  int takeTurn(Monkey *self);
  // Carry out it's operation
  void operation(int no, List *node);
  // Getters
  int getNumber() { return no; }
  int getDivider() { return divisor; }
  int getThrowTrue() { return throwTo[0]; }
  int getThrowFalse() { return throwTo[1]; }
};

void Monkey::operation(int no, List *node) {
  switch (no) {
  case 0:
    node->setValue(node->getValue() * 19);
    break;
  case 1:
    node->setValue(node->getValue() + 6);
    break;
  case 2:
    node->setValue(node->getValue() * node->getValue());
    break;
  case 3:
    node->setValue(node->getValue() + 3);
    break;
  case 4:
    node->setValue(node->getValue() * 17);
    break;
  case 5:
    node->setValue(node->getValue() + 7);
    break;
  case 6:
    node->setValue(node->getValue() + 6);
    break;
  case 7:
    node->setValue(node->getValue() + 3);
    break;
  };
}

// Monkey Member Functions
// Returns -1 if list is empty, hence skip it in a round
int Monkey::takeTurn(Monkey *self) {
  List *temp;
  temp = self->root->getFirst();

  if (temp == NULL) {
    return -1;
  }

  int no = self->getNumber();

  // Perform operation
  operation(no, temp);
  // Perform division test
  if (temp->getValue() / self->getDivider() == 0) {
    return getThrowTrue();
  }
  return getThrowFalse();
}

Monkey *getMonkeys(string filePath) {
  ifstream input;
  input.open(filePath);
  int monkeyCount;
  string line;

  // Get  monkey count
  for (int i = 0; input.peek() != EOF; i++) {
    if (line == "") {
      monkeyCount = i;
    }
  }
  input.close();
  monkeyCount++;

  Monkey *arr = (Monkey *)malloc(sizeof(Monkey) * monkeyCount);
  for (int i = 0; input.peek() != EOF; i++) {
    while (line != "") {
      getline(input, line);
    }
  }

  input.open(filePath);
  input.close();
}

int main(int argc, char **argv) {

  string filePath = argv[1];
  ifstream input;

  return 0;
}