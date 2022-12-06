#include <fstream>
#include <iostream>

using namespace std;

int main() {
  FILE *fptr;
  fptr = fopen("puzzle_input.csv", "r");
  char c = getc(fptr);
  int counter = 0;

  while (c != EOF) {
    c = getc(fptr);
    counter++;
  }
  cout << counter << endl;

  return 0;
}