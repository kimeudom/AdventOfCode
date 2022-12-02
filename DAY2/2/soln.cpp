#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Returns 1 if win, 0 if draw, -1 if loss
int getMove(string line) {
  // Normalise the input
  int oponent = line[0] - 65;
  int state = line[2] - 88;

  /*
  9 possible combinations
    AZ -W [B] 0 2
    BZ -W [C] 1 2
    CZ -W [A] 2 2
    AX -L [C] 0 0
    BX -L [A] 1 0
    CX -L [B] 2 0
    AY -D [A] 0 1
    BY -D [B] 1 1
    CY -D [C] 2 1
  */

  if (oponent == 0 && state == 2) {
    return 'B';
  } else if (oponent == 1 && state == 2) {
    return 'C';
  } else if (oponent == 2 && state == 2) {
    return 'A';
  } else if (oponent == 0 && state == 0) {
    return 'C';
  } else if (oponent == 1 && state == 0) {
    return 'A';
  } else if (oponent == 2 && state == 0) {
    return 'B';
  }

  // else it is a draw
  oponent = line[0]; // Remove normalization
  return oponent;
}

int getPoints(int gameState, char gameMove) {
  int points;
  switch (gameState) {
  case 'X': // Loss
    points = 0;
    break;
  case 'Y': // Draw
    points = 3;
    break;
  case 'Z': // Win
    points = 6;
    break;
  }
  switch (gameMove) {
  case 'A':
    points += 1;
    break;
  case 'B':
    points += 2;
    break;
  case 'C':
    points += 3;
    break;
  }
  return points;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "usage : ./soln <<Puzzle input path>>" << endl;
    return -1;
  }

  // Open file
  ifstream input;
  string filepath = argv[1];
  input.open(filepath);

  if (input.fail()) {
    cerr << "Could not open file" << endl;
    return -2;
  }

  int totalPoints = 0;

  while (input.peek() != EOF) {
    string line;
    // the character the player has chosen
    getline(input, line, '\n');
    char gameState = line[2];
    totalPoints += getPoints(gameState, getMove(line));
  }

  std::cout << totalPoints << endl;

  return 0;
}