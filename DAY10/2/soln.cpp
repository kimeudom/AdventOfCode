#include <fstream>
#include <iostream>

using namespace std;

// Class for the CPU for the CRT handheld comms device
class CPU {
private:
  // The current CPU's cycle count
  int cycleCount;
  // The CPU's X register
  int x;

public:
  CPU() { cycleCount = 0, x = 1; }
  // Getters
  int getCycleCount() { return cycleCount; }
  int getX() { return x; }
  // Setters
  void setX(int value) { x = value; }
  void setCycleCount(int value) { cycleCount = value; }
};

bool endOfScreen(int cc) {
  if (cc == 40 || cc == 80 || cc == 120 || cc == 160 || cc == 200 ||
      cc == 240) {
    return true;
  }
  return false;
}

bool inSpriteRange(int cc, int x) {
  // normalize the data
  int ranges[] = {40, 80, 120, 160, 200, 240};
  for (int i = 5; i >= 0; i--) {
    if (cc - ranges[i] >= 0) {
      cc -= ranges[i];
      break;
    }
  }

  // Sprite width is 3
  // Accounting for the sprite width
  if (cc == x - 1 || cc == x || cc == x + 1) {
    return true;
  }

  return false;
}

void printScreen(string filePath) {

  CPU *processor = new CPU();
  ifstream input;
  input.open(filePath);

  // Error handling
  if (input.fail()) {
    cerr << "Unable to open file" << endl;
    return;
  }

  // Stores an input line from the puzzle input
  string line;

  while (input.peek() != EOF) {
    // Read the next line
    getline(input, line);

    processor->setCycleCount(processor->getCycleCount() + 1);
    int cc = processor->getCycleCount();
    int x = processor->getX();

    // Check if sprite is visible
    (inSpriteRange(cc, x + 1)) ? putc('#', stdout) : putc('.', stdout);

    if (endOfScreen(cc)) {
      cout << endl;
    }

    if (line == "noop") {
      continue;
    }

    // addx operation second step
    processor->setCycleCount(cc + 1);
    cc = processor->getCycleCount();

    // Check if sprite is visible
    (inSpriteRange(cc, x + 1)) ? putc('#', stdout) : putc('.', stdout);

    if (endOfScreen(cc)) {
      cout << endl;
    }
    // The value of the addx operation
    int newX = stoi(line.substr(line.find(" "), line.length()));
    // add the x value to the procesors x register
    processor->setX(processor->getX() + newX);
  }

  // Destroy objects
  delete (processor);
  input.close();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage : ./soln <puzzle_input_path>" << endl;
  }
  string filePath = argv[1];
  ifstream input;

  printScreen(filePath);
  cout << endl;
  return 0;
}