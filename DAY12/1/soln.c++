#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// Globals
int COLS;
int ROWS;
char **_3dMaze;

int start[2];
int goal[2];

void findCoordinates(char **maze, char c, int arr[]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (maze[i][j] == c) {
        arr[0] = i;
        arr[1] = j;
      }
    }
  }
}

// Allocates heap memory to mazes
void allocMem() {
  _3dMaze = (char **)malloc(sizeof(char *) * ROWS);

  for (int i = 0; i < ROWS; i++) {
    _3dMaze[i] = (char *)malloc(sizeof(char) * COLS);
  }
}

// Gets the 3d maze dimentions
void get3DmazeDim(string filePath) {
  ifstream input;
  string line;
  int cols_file = 0;
  int rows_file = 0;

  input.open(filePath);

  // Getting the maze dimentions
  do {
    getline(input, line);

    if (cols_file == 0) {
      cols_file = line.length();
    }
    rows_file++;
  } while (input.peek() != EOF);
  input.close();

  COLS = cols_file;
  ROWS = rows_file;
}

void get3Dmaze(string filePath) {

  int s = filePath.length() + 1;
  char file[s];
  strcpy(file, filePath.c_str());

  FILE *ptr = fopen(file, "r");

  // Set boundaries in the exterior
  for (int i = 0; i < COLS; i++) {
    // Setting the upper and lower boundaries
    _3dMaze[0][i] = '#';
    _3dMaze[ROWS - 1][i] = '#';
  }
  for (int i = 0; i < ROWS; i++) {
    // Setting the left and right boundaries
    _3dMaze[i][0] = '#';
    _3dMaze[i][COLS - 1] = '#';
  }
  for (int i = 1; i < ROWS - 1; i++) {
    for (int j = 1; j < COLS - 1; j++) {
      char c = getc(ptr);
      if (c == '\n') {
        c = getc(ptr);
      }
      _3dMaze[i][j] = c;
    }
  }
  fclose(ptr);
}

void printMaze(char **maze) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      cout << maze[i][j];
    }
    cout << endl;
  }

  cout << endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage :: ./soln <input file>" << endl;
    return -1;
  }

  // Get the maze
  string filePath = "../test.txt";

  get3DmazeDim(filePath);
  // Adding 2 additional rows and columns because we need to create maze
  // boundaries
  ROWS += 2;
  COLS += 2;
  allocMem();

  get3Dmaze(filePath);
  printMaze(_3dMaze);

  // Getting the start and goal destination
  findCoordinates(_3dMaze, 'S', start);
  findCoordinates(_3dMaze, 'E', goal);

  cout << ROWS << " " << COLS << endl;
  return 0;
}