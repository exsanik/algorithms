#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
  int nodeAmount;

  class AdjListNode {
    int v;
    int weight;

   public:
    AdjListNode(int _v, int _w) {
      v = _v;
      weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
  };

  vector<vector<AdjListNode>> adj;

 public:
  explicit Graph(int nodeAmount);

  void addEdge(int u, int v, int weight);

  void dijkstraPath(int start, int finish, bool ifMin = true);
};

Graph::Graph(int nodeAmount) {
  this->nodeAmount = nodeAmount;
  adj.resize(nodeAmount);
}

void Graph::addEdge(int u, int v, int weight) {
  AdjListNode node(v, weight);
  adj[u].push_back(node);  // Add v to u's list
}

void Graph::dijkstraPath(int start, int finish, bool ifMin) {
  vector<int> dist(nodeAmount, INT_MAX);
  vector<int> parents(nodeAmount);
  dist[start] = 0;
  vector<bool> visited(nodeAmount);

  for (int i = 0; i < nodeAmount; ++i) {
    int currentVertex = -1;
    for (int j = 0; j < nodeAmount; ++j)
      if (!visited[j] && (currentVertex == -1 || dist[j] < dist[currentVertex]))
        currentVertex = j;
    if (dist[currentVertex] == INT_MAX) break;
    visited[currentVertex] = true;

    for (size_t j = 0; j < adj[currentVertex].size(); ++j) {
      int to = adj[currentVertex][j].getV();
      int weigth = adj[currentVertex][j].getWeight();
      if (!ifMin) weigth *= -1;

      if (dist[currentVertex] + weigth < dist[to]) {
        dist[to] = dist[currentVertex] + weigth;
        parents[to] = currentVertex;
      }
    }
  }

  vector<int> path;
  for (int v = finish; v != start; v = parents[v]) {
    path.push_back(v);
  }
  path.push_back(start);
  reverse(path.begin(), path.end());

  for (int ver : path) {
    cout << ver + 1 << ((ver == finish) ? " " : " -> ");
  }
  int result = dist[finish];
  if (!ifMin) result *= -1;
  cout << "with cost " << result << endl;
}

int main() {
  Graph g(7);
  g.addEdge(0, 4, 5);
  g.addEdge(0, 1, 10);
  g.addEdge(0, 3, 1);

  g.addEdge(1, 4, 8);
  g.addEdge(1, 2, 9);
  g.addEdge(1, 5, 10);

  g.addEdge(2, 5, 4);
  g.addEdge(2, 3, 3);

  g.addEdge(3, 5, 5);
  g.addEdge(3, 6, 4);

  g.addEdge(4, 5, 7);
  g.addEdge(4, 6, 3);

  g.addEdge(5, 6, 8);

  int start = 0;
  int finish = 6;
  cout << "Shortest critical path from : " << start + 1 << " to " << finish + 1
       << endl;
  g.dijkstraPath(start, finish);

  cout << endl;

  cout << "Longest critical path from : " << start + 1 << " to " << finish + 1
       << endl;
  g.dijkstraPath(start, finish, false);

  return 0;
}
