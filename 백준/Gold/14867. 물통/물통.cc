#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int a, b, c, d;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c >> d;
}

int BreadthFirstSearch() {
  queue<pair<int, int>> q;
  vector<vector<int>> visited(a + 1, vector<int>(b + 1, -1));
  q.push({0, 0});
  visited[0][0] = 0;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int curr1 = p.first;
    int curr2 = p.second;
    q.pop();

    if (curr1 == c && curr2 == d)
      return visited[curr1][curr2];

    // Fill
    if (visited[a][curr2] == -1) {
      q.push({a, curr2});
      visited[a][curr2] = visited[curr1][curr2] + 1;
    }

    if (visited[curr1][b] == -1) {
      q.push({curr1, b});
      visited[curr1][b] = visited[curr1][curr2] + 1;
    }

    // Empty
    if (visited[0][curr2] == -1) {
      q.push({0, curr2});
      visited[0][curr2] = visited[curr1][curr2] + 1;
    }

    if (visited[curr1][0] == -1) {
      q.push({curr1, 0});
      visited[curr1][0] = visited[curr1][curr2] + 1;
    }

    // Move
    int next2 = min(curr1 + curr2, b);
    int next1 = curr1 - (next2 - curr2);
    if (visited[next1][next2] == -1) {
      q.push({next1, next2});
      visited[next1][next2] = visited[curr1][curr2] + 1;
    }

    next1 = min(curr1 + curr2, a);
    next2 = curr2 - (next1 - curr1);
    if (visited[next1][next2] == -1) {
      q.push({next1, next2});
      visited[next1][next2] = visited[curr1][curr2] + 1;
    }
  }

  return -1;
}

void Solve() {
  cout << BreadthFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
