#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

// Global Total
int TotalGlobal = 0;

using namespace std;

// A linked list that stores the sizes of directories in the entire file System
// in no particular order
struct dirSizes {
  string name;
  int size;
  dirSizes *next;
};

// Tree nodes
class TreeNode {
private:
  string name;
  int size;
  TreeNode *parent;
  TreeNode *nextSibling;
  TreeNode *firstChild;

public:
  TreeNode(string DirName);
  TreeNode(string fileName, TreeNode *prt, int value);
  TreeNode *getLastChild();
  void addSibling(TreeNode *sib) { nextSibling = sib; };
  void addFirstChild(TreeNode *chld) { firstChild = chld; };
  void addParent(TreeNode *prt) { parent = prt; };
  TreeNode *getParent() { return parent; };
  TreeNode *getNextSibling() { return nextSibling; };
  TreeNode *getFirstChild() { return firstChild; };
  string getName() { return name; };
  friend int getSize(TreeNode *self);
};

// Class TreeNode memeber functions

// Create a null tree node, helpful for creating directories
TreeNode::TreeNode(string DirName) {
  size = 0;
  parent = NULL;
  nextSibling = NULL;
  firstChild = NULL;
  name = DirName;
}

// Constructor for files (not directories)
TreeNode::TreeNode(string fileName, TreeNode *prt, int value = 0) {
  size = value;
  name = fileName;
  parent = prt;
  nextSibling = NULL;
  firstChild = NULL;
}

// Returns NULL if the node has no children
// or returns the pointer to the last child in the linked list
TreeNode *TreeNode::getLastChild() {
  TreeNode *temp = firstChild;
  if (temp == NULL) {
    // Has no children
    return temp;
  }

  while (temp->nextSibling != NULL) {
    temp = temp->nextSibling;
  }

  // Return last child
  return temp;
}

// Returns the size of the file or the directory beneath it (if present)
int getSize(TreeNode *self) {
  if (self->firstChild == NULL) {
    // Return the file size since it has no children
    return self->size;
  }

  // Traverse the entire tree beneath the directory and return its size
  // Level order traversal
  int sum = 0;
  TreeNode *temp = self->getFirstChild();
  // If we stumble upon a directory, get its size
  while (temp != NULL) {
    sum += getSize(temp);
    temp = temp->getNextSibling();
  }
  return sum;
}

void addChild(TreeNode *prt, TreeNode *chld) {
  if (prt->getFirstChild() == NULL) {
    prt->addFirstChild(chld);
    chld->addParent(prt);
    return;
  }

  TreeNode *last = prt->getLastChild();
  last->addSibling(chld);
  chld->addParent(prt);
  return;
}

void addToList(dirSizes **head, int value, string name) {
  dirSizes *temp = (dirSizes *)malloc(sizeof(dirSizes));

  temp->next = NULL;
  temp->name = name;
  temp->size = value;

  if (*head == NULL) {
    *head = temp;
    return;
  }

  dirSizes *ptr;
  ptr = *head;

  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = temp;
}

// Executes the commands passed from the line inT the current dir
void execCommand_cd(string line, TreeNode *dir, TreeNode **temp) {
  // Available Commands
  // cd [d] [/] [..]
  string command = line.substr(0, 3);

  // Get command argument
  string commandArg = line.substr(5, line.length() - 1);

  if (commandArg == "/") {
    // Go to parent
    while (dir->getParent() != NULL) {
      dir = dir->getParent();
    }
    *temp = dir;
  } else if (commandArg == "..") {
    // Go to above dir
    dir = dir->getParent();
    *temp = dir;
  } else {
    // Change directory to the supplied argument
    TreeNode *dirTemp = dir->getFirstChild();
    while (dirTemp->getName() != commandArg) {
      dirTemp = dirTemp->getNextSibling();
    }
    *temp = dirTemp;
  }
}

void getDirTotals(TreeNode *root, dirSizes **head) {
  int Total = 0;
  // If the current Tree Node has no children it is a file
  if (root->getFirstChild() == NULL) {
    return;
  }

  // Else it is a directory
  // Try and see if the dir is less than 10000;
  Total += getSize(root);
  addToList(head, getSize(root), root->getName());

  // Else move to the children, try and get their sizes
  TreeNode *temp = root->getFirstChild();
  while (temp != NULL) {
    getDirTotals(temp, head);
    temp = temp->getNextSibling();
  }
}

int smallestDir(dirSizes *head) {
  int reminder = 70000000 - head->size;
  int dirSize = 30000000 - reminder;
  dirSizes *temp = head;

  int currDir = temp->size;
  while (temp != NULL) {
    if (temp->size > dirSize && temp->size < currDir) {
      currDir = temp->size;
    }
    temp = temp->next;
  }

  return currDir;
}

void printList(dirSizes *head) {
  if (head == NULL) {
    return;
  }
  dirSizes *temp = head;
  while (temp->next != NULL) {
    cout << temp->size << "->";
    temp = temp->next;
  }
  cout << temp->size << "->";
  cout << endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage :: ./soln <<puzzle input>>" << endl;
    return -1;
  }

  string filename = argv[1];
  ifstream input;
  input.open(filename);

  if (input.fail()) {
    cerr << "Failed to open file" << endl;
    return -2;
  }

  string line;
  // The parent tree Node
  TreeNode *root = new TreeNode("/");
  TreeNode *temp = root;

  // Linked List for the sizes of directories
  dirSizes *head = NULL;

  // 1 if last executed command was ls
  // 0 if not
  int lsExitCode = 0;

  while (input.peek() != EOF) {
    if (lsExitCode != 0) {
      lsExitCode = 0;
    } else {
      getline(input, line, '\n');
    }

    // Differenciate between commands and files
    // Commands start with the (Dollar)$ sign
    // ls and cd commands
    string command;
    command = line.substr(0, 4);

    // Perform command operations
    if (command == "$ cd") {
      // Perform cd operations
      execCommand_cd(line, temp, &temp);
    } else {
      // Perform  ls functionality
      // Command is "$ ls"
      // Perform ls operations
      // Read until line[0] is $ i.e. the next command
      do {
        string isDir;
        getline(input, line, '\n');
        if (line[0] == '$') {
          break;
        }
        isDir = line.substr(0, 3);
        // Move to the line below "ls"
        // Check dir content type
        // dir
        // 7798 [file size]
        if (isDir == "dir") {
          string dirName = line.substr(4, line.length() - 1);
          TreeNode *tempDir = new TreeNode(dirName);
          addChild(temp, tempDir);
        } else {
          // is a file
          // File format
          // [filesize[int]] newFileName
          int fileSize = stoi(line);
          string newFileName =
              line.substr(line.find(' ') + 1, line.length() - 1);
          TreeNode *file = new TreeNode(newFileName, temp, fileSize);
          addChild(temp, file);
        }
      } while (input.peek() != EOF);
      lsExitCode = 1;
    }
  }

  getDirTotals(root, &head);
  cout << smallestDir(head) << endl;
}