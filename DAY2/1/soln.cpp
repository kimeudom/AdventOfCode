#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Returns 1 if win, 0 if draw, -1 if loss
int getGameState(string line) {
  // Normalise the input
  int oponent = line[0] - 65;
  int player = line[2] - 88;

  /*
  nine possible combinations
  (AX)RR - D
  (BY)PP - D
  (CZ)SS - D
  (AY)RP - W
  (BZ)PS - W
  (CX)SR - W
  (BX)PR - L
  (CY)SP - L
  (AZ)RS - L
  */
  if (oponent == 0 && player == 1) {
    return 1;
  } else if (oponent == 1 && player == 2) {
    return 1;
  } else if (oponent == 2 && player == 0) {
    return 1;
  } else if (oponent == 1 && player == 0) {
    return -1;
  } else if (oponent == 2 && player == 1) {
    return -1;
  } else if (oponent == 0 && player == 2) {
    return -1;
  }

  // If all else fails, it is a draw
  return 0;
}

int getPoints(int gameState, char charChosen) {
  int points;
  switch (gameState) {
  case 1:
    points = 6; // Win
    break;
  case 0:
    points = 3; // Draw
    break;
  case -1:
    points = 0; // Loss
    break;
  }

  switch (charChosen) {
  case 'X':
    points += 1; // Chose rock
    break;
  case 'Y':
    points += 2; // Chose paper
    break;
  case 'Z':
    points += 3; // Chose scissors
    break;
  };

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
    char charChosen = line[2];

    totalPoints += getPoints(getGameState(line), charChosen);
  }

  std::cout << totalPoints << endl;

  return 0;
}