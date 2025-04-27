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
    
    vector<int> moves1 = { 1, -1, a, -a, b, -b };
    for (int i = 0; i < ssize(moves1); ++i) {
      int next_val = curr_val + moves1[i];
      
      if (next_val < 0 || next_val > 100'000)
        continue;
      
      int& visit = visited[next_val];
      if (visit != -1)
        continue;
      
      q.push(next_val);
      visit = visited[curr_val] + 1;
    }

    vector<int> moves2 = { a, b };
    for (int i = 0; i < ssize(moves2); ++i) {
      int next_val = curr_val * moves2[i];
      
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