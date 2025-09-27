#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int n) : parents_(n), sizes_(n, 1) {
    for (int i = 0; i < n; ++i)
      parents_[i] = i;
  }

  int Find(int x) {
    if (x == parents_[x])
      return x;
    return parents_[x] = Find(parents_[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y)
      return false;

    if (sizes_[x] < sizes_[y])
      swap(x, y);

    parents_[y] = x;
    sizes_[x] += sizes_[y];
    return true;
  }

 private:
  vector<int> parents_, sizes_;
};

int n, k, r;
vector<vector<pair<int, int>>> roads;
vector<pair<int, int>> cows;
vector<vector<vector<bool>>> road_map(100,
                                      vector<vector<bool>>(100,
                                                           vector<bool>(2)));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k >> r;

  roads.resize(r);
  for (int i = 0; i < r; ++i) {
    int r, c, r_prime, c_prime;
    cin >> r >> c >> r_prime >> c_prime;
    roads[i].push_back({r - 1, c - 1});
    roads[i].push_back({r_prime - 1, c_prime - 1});
  }

  cows.resize(k);
  for (int i = 0; i < k; ++i)
    cin >> cows[i].first >> cows[i].second;
}

int GetIndex(int row, int col) {
  return row * (n + 1) + col;
}

void Solve() {
  for (int i = 0; i < k; ++i) {
    --cows[i].first;
    --cows[i].second;
  }

  for (int i = 0; i < r; ++i) {
    pair<int, int> p1 = roads[i][0];
    pair<int, int> p2 = roads[i][1];

    if (p1 > p2)
      swap(p1, p2);

    if (p1.first == p2.first)
      road_map[p1.first][p1.second][0] = true;
    else
      road_map[p1.first][p1.second][1] = true;
  }

  UnionFind union_find((n + 1) * (n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!road_map[i][j][0]) {
        union_find.Union(GetIndex(i, j), GetIndex(i, j + 1));
      }

      if (!road_map[i][j][1]) {
        union_find.Union(GetIndex(i, j), GetIndex(i + 1, j));
      }
    }
  }

  int answer = 0;
  for (int i = 0; i < k; ++i) {
    int parent1 = union_find.Find(GetIndex(cows[i].first, cows[i].second));
    for (int j = i + 1; j < k; ++j) {
      int parent2 = union_find.Find(GetIndex(cows[j].first, cows[j].second));
      if (parent1 != parent2) {
        ++answer;
      }
    }
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
