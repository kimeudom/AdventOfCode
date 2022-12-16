#include "tools.h"
#include <iostream>

using namespace std;

// Hardcoded from the test input
int monkeyBusinessPuzzle() {
  // Create the monkeys
  Monkey *m0 = new Monkey(3, 7, 3, 0);
  m0->addToList(56);
  m0->addToList(56);
  m0->addToList(92);
  m0->addToList(65);
  m0->addToList(71);
  m0->addToList(61);
  m0->addToList(79);
  Monkey *m1 = new Monkey(6, 4, 11, 1);
  m1->addToList(61);
  m1->addToList(85);
  Monkey *m2 = new Monkey(0, 7, 7, 2);
  m2->addToList(54);
  m2->addToList(96);
  m2->addToList(82);
  m2->addToList(78);
  m2->addToList(69);
  Monkey *m3 = new Monkey(5, 1, 2, 3);
  m3->addToList(57);
  m3->addToList(59);
  m3->addToList(65);
  m3->addToList(95);
  Monkey *m4 = new Monkey(2, 6, 19, 4);
  m4->addToList(62);
  m4->addToList(67);
  m4->addToList(80);
  Monkey *m5 = new Monkey(1, 4, 5, 5);
  m5->addToList(91);
  Monkey *m6 = new Monkey(2, 0, 17, 6);
  m6->addToList(79);
  m6->addToList(83);
  m6->addToList(64);
  m6->addToList(52);
  m6->addToList(77);
  m6->addToList(56);
  m6->addToList(63);
  m6->addToList(92);
  Monkey *m7 = new Monkey(3, 5, 13, 7);
  m7->addToList(50);
  m7->addToList(97);
  m7->addToList(76);
  m7->addToList(96);
  m7->addToList(80);
  m7->addToList(56);

  Monkey *arr[] = {m0, m1, m2, m3, m4, m5, m6, m7};

  for (int i = 0; i < 20; i++) {
    int throwTo;
    // Monkey takes turn, throws first node to next monkey
    m0->takeTurn(m0, arr);
    m1->takeTurn(m1, arr);
    m2->takeTurn(m2, arr);
    m3->takeTurn(m3, arr);
    m4->takeTurn(m4, arr);
    m5->takeTurn(m5, arr);
    m6->takeTurn(m6, arr);
    m7->takeTurn(m7, arr);
  }
  // number of monkey inspections
  int m0i = m0->noOfInspections;
  int m1i = m1->noOfInspections;
  int m2i = m2->noOfInspections;
  int m3i = m3->noOfInspections;
  int m4i = m4->noOfInspections;
  int m5i = m5->noOfInspections;
  int m6i = m6->noOfInspections;
  int m7i = m7->noOfInspections;

  // Get the number of incrimented inspections from the monkeys
  int arrInspections[] = {m0i, m1i, m2i, m3i, m4i, m5i, m6i, m7i};

  // Sort the array
  bubbleSort(arrInspections, 8);

  return arrInspections[0] * arrInspections[1];
}
int main(int argc, char **argv) {
  cout << monkeyBusinessPuzzle() << endl;
  return 0;
}