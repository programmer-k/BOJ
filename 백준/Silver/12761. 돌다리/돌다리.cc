#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int a, b, n, m;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> a >> b >> n >> m;
}

int BreadthFirstSearch() {
  queue<int> q;
  vector<int> visited(100'001, -1);
  q.push(n);
  visited[n] = 0;

  while (!q.empty()) {
    int curr_val = q.front();
    q.pop();

    if (curr_val == m)
      return visited[curr_val];
    
    vector<int> nexts = { curr_val + 1, curr_val - 1, curr_val + a, curr_val - a, curr_val + b, curr_val -b, curr_val * a, curr_val * b };
    for (int i = 0; i < ssize(nexts); ++i) {
      int next_val = nexts[i];
      
      if (next_val < 0 || next_val > 100'000)
        continue;
      
      int& visit = visited[next_val];
      if (visit != -1)
        continue;
      
      q.push(next_val);
      visit = visited[curr_val] + 1;
    }
  }

  return -1;
}

void Solve() {
  cout << BreadthFirstSearch() << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}