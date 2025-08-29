#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const int kNode = 52;
int n;
vector<vector<int>> flow(kNode, vector<int>(kNode)), capacity(kNode, vector<int>(kNode));

int Convert(int ch) {
  if (ch >= 'A' && ch <= 'Z')
    return ch - 'A';
  return ch - 'a' + 26;
}

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    char a, b;
    int f;
    cin >> a >> b >> f;

    a = Convert(a);
    b = Convert(b);

    capacity[a][b] += f;
    capacity[b][a] += f;
  }
}

void EdmondsKarp(int source, int sink) {
  int total_flow = 0;
  
  while (true) {
    queue<int> q;
    vector<int> parents(kNode, -1);

    q.push(source);
    parents[source] = source;

    while (!q.empty() && parents[sink] == -1) {
      int curr = q.front();
      q.pop();

      for (int next = 0; next < kNode; ++next) {
        if (capacity[curr][next] - flow[curr][next] > 0 && parents[next] == -1) {
          q.push(next);
          parents[next] = curr;
        }
      }
    }

    if (parents[sink] == -1)
      break;

    int max_flow = numeric_limits<int>::max();
    for (int i = sink; i != source; i = parents[i])
      max_flow = min(max_flow, capacity[parents[i]][i] - flow[parents[i]][i]);

    for (int i = sink; i != source; i = parents[i]) {
      flow[parents[i]][i] += max_flow;
      flow[i][parents[i]] -= max_flow;
    }

    total_flow += max_flow;
  }

  cout << total_flow << '\n';
}

void Solve() {
  EdmondsKarp(0, 25);
}

int main() {
  GetInput();
  Solve();
  return 0;
}
