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

// Checks to see if the current CPU cycle is a check point
bool checkpoint(int cc) {
  if (cc == 20 || cc == 60 || cc == 100 || cc == 140 || cc == 180 ||
      cc == 220) {
    return true;
  }

  return false;
}

int SignalStrengthTotal(string filePath) {
  // Stores the running total of the signal strength
  int total = 0;

  CPU *processor = new CPU();
  ifstream input;
  input.open(filePath);

  // Error handling
  if (input.fail()) {
    cerr << "Unable to open file" << endl;
    return -2;
  }

  // Stores an input line from the puzzle input
  string line;

  while (input.peek() != EOF) {
    // Read the next line
    getline(input, line);

    processor->setCycleCount(processor->getCycleCount() + 1);
    int cc = processor->getCycleCount();
    int x = processor->getX();

    // noop operation or addx operation
    // their first steps are similar
    if (checkpoint(cc)) {
      total += cc * x;
    }
    // Skip loop execution if it is a no operation instruction
    if (line == "noop") {
      continue;
    }

    // addx operation second step
    processor->setCycleCount(cc + 1);
    cc = processor->getCycleCount();

    if (checkpoint(cc)) {
      total += cc * x;
    }

    // The value of the addx operation
    int newX = stoi(line.substr(line.find(" "), line.length()));
    // add the x value to the procesors x register
    processor->setX(processor->getX() + newX);
  }

  // Destroy objects
  delete (processor);
  input.close();

  // Return the total
  return total;
}
int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage : ./soln <puzzle_input_path>" << endl;
  }
  string filePath = argv[1];
  ifstream input;

  cout << SignalStrengthTotal(filePath) << endl;

  return 0;
}