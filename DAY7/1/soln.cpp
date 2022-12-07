#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

// Tree nodes
struct Node {
  string name;
  int size;
  vector<Node *> child;
};

// Adding new nodes to a tree
Node *addNewNode(int value) {
  Node *temp = new Node;
  temp->size = value;
  return temp;
}

int sumOfDir(Node *root) {
  // Sum total variable

  int total = 0;

  if (root == NULL) {
    return 0;
  }

  // Create queue to push the root into
  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    int n = q.size();
    while (n > 0) {

      Node *p = q.front();
      q.pop();
      total += p->size;

      // Enqueue all children of the dequeued node
      for (int i = 0; i < p->child.size(); i++) {
        q.push(p->child[i]);
        n--;
      }
    }
  }

  return total;
}

int main() {
  Node *root = addNewNode(0);

  return 0;
}