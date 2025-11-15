#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

struct PairHash {
  size_t operator()(const pair<int, int>& p) const {
    size_t hash1 = hash<int>{}(p.first);
    size_t hash2 = hash<int>{}(p.second);
    return hash1 ^ hash2;
  }
};

int a, b, c, d;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c >> d;
}

int BreadthFirstSearch() {
  queue<pair<int, int>> q;
  unordered_map<pair<int, int>, int, PairHash> visited;
  q.push({0, 0});
  visited[make_pair(0, 0)] = 0;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int curr1 = p.first;
    int curr2 = p.second;
    q.pop();

    if (curr1 == c && curr2 == d)
      return visited[make_pair(curr1, curr2)];

    // Fill
    if (!visited.contains(make_pair(a, curr2))) {
      q.push({a, curr2});
      visited[make_pair(a, curr2)] = visited[make_pair(curr1, curr2)] + 1;
    }

    if (!visited.contains(make_pair(curr1, b))) {
      q.push({curr1, b});
      visited[make_pair(curr1, b)] = visited[make_pair(curr1, curr2)] + 1;
    }

    // Empty
    if (!visited.contains(make_pair(0, curr2))) {
      q.push({0, curr2});
      visited[make_pair(0, curr2)] = visited[make_pair(curr1, curr2)] + 1;
    }

    if (!visited.contains(make_pair(curr1, 0))) {
      q.push({curr1, 0});
      visited[make_pair(curr1, 0)] = visited[make_pair(curr1, curr2)] + 1;
    }

    // Move
    int next2 = min(curr1 + curr2, b);
    int next1 = curr1 - (next2 - curr2);
    if (!visited.contains(make_pair(next1, next2))) {
      q.push({next1, next2});
      visited[make_pair(next1, next2)] = visited[make_pair(curr1, curr2)] + 1;
    }

    next1 = min(curr1 + curr2, a);
    next2 = curr2 - (next1 - curr1);
    if (!visited.contains(make_pair(next1, next2))) {
      q.push({next1, next2});
      visited[make_pair(next1, next2)] = visited[make_pair(curr1, curr2)] + 1;
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
