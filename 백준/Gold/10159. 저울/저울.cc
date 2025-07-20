#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int kIntMax = numeric_limits<int>::max();
int n, m;
vector<vector<int>> edges(101);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node2].push_back(node1);
  }
}

void FloydWarshall() {
  vector<vector<int>> dists(n + 1, vector<int>(n + 1, kIntMax));

  for (int i = 1; i <= n; ++i)
    dists[i][i] = 0;

  for (int i = 1; i <= n; ++i) {
    for (int edge : edges[i]) {
      dists[i][edge] = 1;
    }
  }

  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (dists[i][k] != kIntMax && dists[k][j] != kIntMax && dists[i][k] + dists[k][j] < dists[i][j]) {
          dists[i][j] = dists[i][k] + dists[k][j];
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    int count = 0;
    for (int j = 1; j <= n; ++j) {
      if (dists[i][j] != kIntMax || dists[j][i] != kIntMax) {
        ++count;
      }
    }

    cout << n - count << '\n';
  }
}

void Solve() {
  FloydWarshall();
}

int main() {
  GetInput();
  Solve();
  return 0;
}