#include <fstream>
#include <iostream>
#include <set>
#include <stdlib.h>
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

bool isAdjacent(RopeEnd *h, RopeEnd *t) {
  int tx, ty, hx, hy;
  tx = t->getX();
  ty = t->getY();
  hx = h->getX();
  hy = h->getY();
  // Is adjacent if H and T are in the same position
  if (hx == tx && hy == ty) {
    return true;
  }

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

void moveTail(RopeEnd *h, RopeEnd *t) {
  int tx, ty, hx, hy;
  tx = t->getX();
  ty = t->getY();
  hx = h->getX();
  hy = h->getY();

  if (hy == ty) {
    // Horizontal movement
    (hx > tx) ? t->setX(tx + 1) : t->setX(tx - 1);
    return;
  } else if (hx == tx) {
    //  Diagonal movement
    (hy > ty) ? t->setY(ty + 1) : t->setY(ty - 1);
    return;
  }

  //  Diagonal movement
  bool UR = ((hx > tx) && (hy > ty));
  bool UL = ((hx < tx) && (hy > ty));
  bool LR = ((hx > tx) && (hy < ty));
  bool LL = ((hx < tx) && (hy < ty));

  if (UR) {
    t->setX(tx + 1);
    t->setY(ty + 1);
    return;
  } else if (UL) {
    t->setX(tx - 1);
    t->setY(ty + 1);
    return;
  } else if (LR) {
    t->setX(tx + 1);
    t->setY(ty - 1);
    return;
  } else if (LL) {
    t->setX(tx - 1);
    t->setY(ty - 1);
    return;
  }
}

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

int main(int argc, char **argv) {

  string filename = argv[1];
  ifstream input;
  input.open(filename);

  string line;
  RopeEnd *h = new RopeEnd();
  RopeEnd *t = new RopeEnd();
  // A set to store the visited coordinates
  set<pair<int, int>> s;
  // Add the origin directory
  s.insert({0, 0});

  while (input.peek() != EOF) {
    getline(input, line, '\n');
    char dir = line[0];
    int counter = line[2] - '0';
    // cout << line << endl;

    for (int i = 0; i < counter; i++) {
      moveHead(h, dir);
      if (!isAdjacent(h, t)) {
        moveTail(h, t);
        s.insert({t->getX(), t->getY()});
      }
      // cout << "(" << h->getX() << "," << h->getY() << ")";
      // cout << "(" << t->getX() << "," << t->getY() << ")" << endl;
    }
  }

  cout << s.size() << endl;

  return 0;
}