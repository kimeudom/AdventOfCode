#include <fstream>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <unistd.h>
#include <utility>

using namespace std;

// A class to store a rope end, either Tail or Head
class RopeEnd {
private:
  // The coordinates of the rope element at a particular time
  int x;
  int y;

public:
  // Constructor initializes the coordinates of the rope end at the origin point
  RopeEnd() { x = 0, y = 0; };
  void setX(int xCoord) { x = xCoord; }
  void setY(int yCoord) { y = yCoord; }
  int getX() { return x; }
  int getY() { return y; }
};

bool isAdjacent(int tx, int ty, int hx, int hy) {
  // Is adjacent if H and T are in the same position
  if (hx == tx && hy == ty) {
    return true;
  }

  // Checking x and y planes
  if (hy == ty) {
    // Check Horizontal
    if (hx == tx - 1 || hx == tx + 1) {
      return true;
    }
  } else if (hx == tx) {
    // Check Vertical
    if (hy == ty - 1 || hy == ty + 1) {
      return true;
    }
  }
  // Check Diagonal
  bool UR = ((hx == tx - 1) && (hy == ty - 1));
  bool UL = ((hx == tx + 1) && (hy == ty - 1));
  bool LR = ((hx == tx - 1) && (hy == ty + 1));
  bool LL = ((hx == tx + 1) && (hy == ty + 1));

  if (UR || UL || LR || LL) {
    return true;
  }

  // If all checks fail, the rope ends are not adjacent
  return false;
}

void moveTail(RopeEnd *h, RopeEnd *t, int tx, int ty, int hx, int hy) {
  if (hy == ty) {
    // Horizontal movement
    (hx > tx) ? t->setX(tx + 1) : t->setX(tx - 1);
    return;
  } else if (hx == tx) {
    //  Vertical movement
    (hy > ty) ? t->setY(ty + 1) : t->setY(ty - 1);
    return;
  }

  //  Diagonal movement
  bool UR = ((hx > tx) && (hy > ty));
  bool UL = ((hx < tx) && (hy > ty));
  bool LR = ((hx > tx) && (hy < ty));
  bool LL = ((hx < tx) && (hy < ty));

  if (UR) {
    t->setX(tx + 1), t->setY(ty + 1);
    return;
  } else if (UL) {
    t->setX(tx - 1), t->setY(ty + 1);
    return;
  } else if (LR) {
    t->setX(tx + 1), t->setY(ty - 1);
    return;
  } else if (LL) {
    t->setX(tx - 1), t->setY(ty - 1);
  }
}

// Moves the head one step in the specified direction dir
void moveHead(RopeEnd *h, char dir) {
  switch (dir) {
  case 'R':
    h->setX(h->getX() + 1);
    break;
  case 'L':
    h->setX(h->getX() - 1);
    break;
  case 'U':
    h->setY(h->getY() + 1);
    break;
  case 'D':
    h->setY(h->getY() - 1);
    break;
  };
}

void addNull(char arr[][36]) {
  for (int i = 0; i < 36; i++) {
    for (int j = 0; j < 36; j++) {
      arr[i][j] = ' ';
    }
  }
}

void printArr(char arr[][36]) {
  for (int i = 0; i < 36; i++) {
    for (int j = 0; j < 36; j++) {
      cout << "[" << arr[i][j] << "] ";
    }
    cout << endl;
  }
}

void addToArr(char arr[][36], int x, int y, char c) {
  if (c == 'H') {
    if (arr[x + 17][y + 17] != '#') {
      arr[x + 17][y + 17] = '*';
    }
  } else {
    arr[x + 17][y + 17] = '#';
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage : ./soln <<puzzle input>>" << endl;
    return -1;
  }

  string filename = argv[1];
  ifstream input;
  input.open(filename);

  if (input.fail()) {
    cerr << "Could not open file " << endl;
    return -2;
  }

  string line;
  RopeEnd *h = new RopeEnd();
  RopeEnd *t = new RopeEnd();
  // A set to store the visited coordinates
  set<pair<int, int>> s;
  // Add the origin directory
  s.insert({0, 0});

  // Fill the arr
  char arr[36][36];
  addNull(arr);

  while (input.peek() != EOF) {

    getline(input, line, '\n');
    char dir = line[0];
    int counter = line[2] - '0';
    // cout << line << endl;

    for (int i = 0; i < counter; i++) {
      system("clear");
      moveHead(h, dir);
      addToArr(arr, h->getX(), h->getY(), 'H');
      printArr(arr);
      sleep(2);
      int tx, ty, hx, hy;
      tx = t->getX(), ty = t->getY(), hx = h->getX(), hy = h->getY();

      if (!isAdjacent(tx, ty, hx, hy)) {
        system("clear");
        moveTail(h, t, tx, ty, hx, hy);
        addToArr(arr, t->getX(), t->getY(), 'T');
        printArr(arr);
        sleep(2);

        s.insert({t->getX(), t->getY()});
      }
    }
  }

  cout << s.size() << endl;

  return 0;
}