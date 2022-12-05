#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Stack {
private:
  // The stack max size is derived from the input stack elements total
  int data[56];

  // Stack indexes
  int top = -1;
  int bottom = 0;

public:
  char peek();
  void push(int element);
  int pop();
  void displayStack();
};

// Member functions definitions
char Stack::peek() { return (char)data[top]; }

void Stack::push(int element) {
  top += 1;
  data[top] = element;
}

// Return the top element value
int Stack::pop() {
  int temp = top;
  top -= 1;
  return data[temp];
}

void Stack::displayStack() {
  if (top == 0) {
    cout << data[top] << endl;
    return;
  } else {
    for (int i = top; i >= 0; i--) {
      cout << (char)data[i] << " ->";
    }
  }
}

// Add stacks to the 2D char array
// Very dirty, I know
// Could not think of a better solution
// In the input data, the stack containers are founds in positions
// 1 5 9 13 17 21 25 29 33 of the line
void getStacks(char arr[][9], string line, int rowCount) {
  int j = 0;
  for (int i = 0; i < line.length(); i++) {
    if (i == 1 || i == 5 || i == 9 || i == 13 || i == 17 || i == 21 ||
        i == 25 || i == 29 || i == 33) {
      if (isalnum(line[i])) {
        arr[rowCount][j] = line[i];
        j++;
      } else {
        arr[rowCount][j] = ' ';
        j++;
      }
    }
    if (j > 8) {
      return;
    }
  }
}

void addToStack(Stack *x, char arr[][9], int column) {
  for (int i = 7; i >= 0; i--) {
    if (arr[i][column] == ' ') {
      return;
    }
    x->push(arr[i][column]);
  }
}

void getFinalChars(Stack S[]) {
  for (int i = 0; i < 9; i++) {
    cout << S[i].peek();
  }
  cout << endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage :: ./soln << puzzle input path>>" << endl;
    return -1;
  }

  ifstream input;
  string filename = "puzzle_input.csv";
  // string filename = argv[1];
  input.open(filename);

  // A line from the puzzle input file
  string line;
  char input_stacks[8][9];
  int rowCount = 0;

  // Get the input stacks
  for (int i = 0; i < 8; i++) {
    getline(input, line, '\n');
    getStacks(input_stacks, line, i);
  }

  // Add the input stacks to the stack object
  // 9 stack objects from a to i
  Stack S[9];
  addToStack(&S[0], input_stacks, 0);
  addToStack(&S[1], input_stacks, 1);
  addToStack(&S[2], input_stacks, 2);
  addToStack(&S[3], input_stacks, 3);
  addToStack(&S[4], input_stacks, 4);
  addToStack(&S[5], input_stacks, 5);
  addToStack(&S[6], input_stacks, 6);
  addToStack(&S[7], input_stacks, 7);
  addToStack(&S[8], input_stacks, 8);

  // Get Movements
  // Skip 2 input lines
  getline(input, line, '\n');
  getline(input, line, '\n');

  int from;
  int to;
  int amount;

  while (input.peek() != EOF) {
    getline(input, line, '\n');
    amount = stoi(line.substr(line.find("from") - 3, line.find("from")));
    from = stoi(line.substr(line.find("to") - 2, line.find("to") - 2)) - 1;
    to = stoi(line.substr(line.find("to") + 3, line.find("to") + 3)) - 1;

    for (int i = 0; i < amount; i++) {
      S[to].push(S[from].pop());
    }
  }

  getFinalChars(S);

  return 0;
}
