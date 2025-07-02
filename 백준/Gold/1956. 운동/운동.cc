#include <iostream>
#include <array>
#include <limits>
#include <vector>
using namespace std;

const int kIntMax = numeric_limits<int>::max();
int v, e;
vector<vector<int>> dists(401, vector<int>(401, kIntMax));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> v >> e;
  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    dists[a][b] = c;
  }
}

void FloydWarshall() {
  for (int j = 1; j <= v; ++j)
    for (int i = 1; i <= v; ++i)
      for (int k = 1; k <= v; ++k)
        if (dists[i][j] != kIntMax && dists[j][k] != kIntMax && dists[i][k] > dists[i][j] + dists[j][k])
          dists[i][k] = dists[i][j] + dists[j][k];
}

void Solve() {
  FloydWarshall();

  int min_cycle = kIntMax;
  for (int i = 1; i <= v; ++i)
    for (int j = 1; j <= v; ++j)
      if (dists[i][j] != kIntMax && dists[j][i] != kIntMax)
        min_cycle = min(min_cycle, dists[i][j] + dists[j][i]);
  
  if (min_cycle == kIntMax)
    cout << "-1\n";
  else
    cout << min_cycle << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}