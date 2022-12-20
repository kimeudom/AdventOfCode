#include <cmath>
#include <iostream>
#include <string.h>

using namespace std;

struct Node {
  int data;
  Node *next;
};

// Enqueue operations
// Overloaded for both pointers and creating new noses

// Add a pointer of a list node to the end of a list
void enqueue(Node *ptr, Node **head) {
  if (*head == NULL) {
    *head = ptr;
    return;
  }
  Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = ptr;
}

// Create a node at the end of a list with a set value
void enqueue(int value, Node **head) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->data = value;
  temp->next = NULL;

  if (*head == NULL) {
    *head = temp;
    return;
  }

  Node *ptr = *head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = temp;
}

// Removes the first element from a list
Node *dequeue(Node **head) {
  Node *temp = *head;
  *head = temp->next;
  temp->next = NULL;
  return temp;
}
class Monkey {
private:
  Node *root;
  int divisor;
  int noOfInspections;
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
    noOfInspections = 0;
  }
  // Plays it's turn
  void takeTurn(Monkey *self, Monkey *monArr[]);
  // Carry out it's operation (Its operation on the worry level)
  void operation(int no, Node *node);

  void addToList(int value);
  // Getters
  int getNumber() { return no; }
  int getDivider() { return divisor; }
  int getThrowTrue() { return throwTo[0]; }
  int getThrowFalse() { return throwTo[1]; }
  int getInspections() { return noOfInspections; }
  // Setters
  void incrimentInspections() { noOfInspections++; }
  friend long long int monkeyBusinessTest();
  friend long long int monkeyBusinessPuzzle();
  friend void showTimesInspected(Monkey *arr[], int size);
};

// Add a new node value to the end of a list
void Monkey::addToList(int value) {
  Node *temp = new Node();
  temp->data = value;
  temp->next = NULL;

  enqueue(temp, &root);
}

void Monkey::operation(int no, Node *node) {
  switch (no) {
  case 0:
    // node->data = (node->data * 19); // For test input
    node->data = (node->data * 7);
    break;
  case 1:
    // node->data = (node->data + 6); // For test input
    node->data = (node->data + 5);
    break;
  case 2:
    // node->data = (pow(node->data, 2)); // For test input
    node->data = (node->data * node->data);
    break;
  case 3:
    // node->data = (node->data + 3); // For test input
    node->data = (node->data + 4);
    break;
  case 4:
    node->data = (node->data * 17);
    break;
  case 5:
    node->data = (node->data + 7);
    break;
  case 6:
    node->data = (node->data + 6);
    break;
  case 7:
    node->data = (node->data + 3);
    break;
  };
}

// Monkey Member Functions
// Inspects and releases all objects in it's possesion
void Monkey::takeTurn(Monkey *self, Monkey *monArr[]) {

  // Skip this monkey, it has no items
  if (self->root == NULL) {
    return;
  }

  Node *temp;
  temp = self->root;
  int no = self->getNumber();

  do {
    // Perform operation
    operation(no, temp);
    // Incriment the number of inspections
    self->incrimentInspections();

    // Floor division of worry level by 3
    // temp->data = (floor(temp->data / 3));

    // Perform division test
    int throwTo;
    int divisionResult = temp->data % self->getDivider();

    if (divisionResult == 0) {
      throwTo = self->getThrowTrue();
    } else if (divisionResult != 0) {
      throwTo = self->getThrowFalse();
    }

    enqueue(dequeue(&self->root), &monArr[throwTo]->root);

    temp = self->root;
  } while (root != NULL);
}

void printList(Node **head) {
  Node *ptr;
  if (*head == NULL) {
    cout << "{}" << endl;
  } else {
    ptr = *head;
    while (ptr != NULL) {
      cout << ptr->data << " ->";
      ptr = ptr->next;
    }
  }
  printf("NULL\n");
}

void bubbleSort(int arr[], int size) {
  // sort highest to lowest
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}
// Checks to see if the current CPU cycle is a check point
bool checkpoint(int cc) {
  if (cc == 1 || cc == 20 || cc == 1000 || cc == 2000 || cc == 3000 ||
      cc == 4000 || cc == 5000 || cc == 6000 || cc == 7000 || cc == 8000 ||
      cc == 9000 || cc == 10000) {
    return true;
  }

  return false;
}

void showTimesInspected(Monkey *arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << "Monkey " << i << " items :-> " << arr[i]->noOfInspections << endl;
  }
}

// Hardcoded from the test input
long long int monkeyBusinessTest() {
  // Create the monkeys
  Monkey *m0 = new Monkey(2, 3, 23, 0);
  m0->addToList(79);
  m0->addToList(98);
  Monkey *m1 = new Monkey(2, 0, 19, 1);
  m1->addToList(54);
  m1->addToList(65);
  m1->addToList(75);
  m1->addToList(74);
  Monkey *m2 = new Monkey(1, 3, 13, 2);
  m2->addToList(79);
  m2->addToList(60);
  m2->addToList(97);
  Monkey *m3 = new Monkey(0, 1, 17, 3);
  m3->addToList(74);

  Monkey *arr[] = {m0, m1, m2, m3};

  for (int i = 0; i < 10000; i++) {
    // Monkey takes turn, throws first node to next monkey
    // IF take turn result is == -1, it is empty so skip
    m0->takeTurn(m0, arr);
    m1->takeTurn(m1, arr);
    m2->takeTurn(m2, arr);
    m3->takeTurn(m3, arr);
    if (checkpoint(i + 1)) {
      showTimesInspected(arr, 4);
      cout << endl << endl;
    }
  }

  // Get the number of incrimented inspections from the monkeys
  int arrInspections[] = {m0->noOfInspections, m1->noOfInspections,
                          m2->noOfInspections, m3->noOfInspections};

  // Sort the array
  bubbleSort(arrInspections, 4);

  return arrInspections[0] * arrInspections[1];
}