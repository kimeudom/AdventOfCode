#include <bits/stdc++.h>

using namespace std;

// Dijkstra's Algorithim globals

// Infinate value (Untravelled)
#define INF 0x3f3f3f3f

// Integer pairs
typedef pair<int, int> iPair;

// Graph class

class Graph {
private:
  int Vertices;
  list<pair<int, int>> *adjacent;

public:
  Graph(int V);

  void addEdge(int u, int v, int w);
  void shortestPath(int s);
};
