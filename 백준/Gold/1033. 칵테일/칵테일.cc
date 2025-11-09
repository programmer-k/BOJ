#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : parents_(size), curr_ratios_(size) {
    for (int i = 0; i < size; ++i)
      parents_[i] = i;
  }

  int Find(int x) {
    if (x == parents_[x])
      return x;
    return parents_[x] = Find(parents_[x]);
  }

  bool Union(int x, int y, int ratio_x, int ratio_y) {
    int parent_x = Find(x);
    int parent_y = Find(y);

    if (parent_x == parent_y)
      return false;

    if (curr_ratios_[x] == 0 && curr_ratios_[y] == 0) {
      curr_ratios_[x] = ratio_x;
      curr_ratios_[y] = ratio_y;
    } else if (curr_ratios_[x] != 0 && curr_ratios_[y] == 0) {
      int lcm_val = lcm(curr_ratios_[x], ratio_x);
      curr_ratios_[y] = ratio_y * (lcm_val / ratio_x);

      int mult = lcm_val / curr_ratios_[x];
      for (int i = 0; i < ssize(parents_); ++i)
        if (Find(i) == parent_x)
          curr_ratios_[i] *= mult;
    } else if (curr_ratios_[x] == 0 && curr_ratios_[y] != 0) {
      return Union(y, x, ratio_y, ratio_x);
    } else {
      int lcm_val_x = lcm(curr_ratios_[x], ratio_x);
      int lcm_val_y = lcm(curr_ratios_[y], ratio_y);

      int mult_x = (lcm_val_x / curr_ratios_[x]) * (lcm_val_y / ratio_y);
      int mult_y = (lcm_val_y / curr_ratios_[y]) * (lcm_val_x / ratio_x);

      for (int i = 0; i < ssize(parents_); ++i)
        if (Find(i) == parent_x)
          curr_ratios_[i] *= mult_x;
        else if (Find(i) == parent_y)
          curr_ratios_[i] *= mult_y;
    }

    int gcd_val = curr_ratios_[parent_x];
    for (int i = 0; i < ssize(parents_); ++i)
      if (Find(i) == parent_x || Find(i) == parent_y)
        gcd_val = gcd(gcd_val, curr_ratios_[i]);

    if (gcd_val > 1)
      for (int i = 0; i < ssize(parents_); ++i)
        if (Find(i) == parent_x || Find(i) == parent_y)
          curr_ratios_[i] /= gcd_val;

    parents_[parent_y] = parent_x;
    return true;
  }

  int GetRatio(int index) {
    return curr_ratios_[index];
  }

 private:
  vector<int> parents_, curr_ratios_;
};

int n;
vector<vector<pair<int, int>>> ratios(10, vector<pair<int, int>>(10));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b, p, q;
    cin >> a >> b >> p >> q;

    int gcd_val = gcd(p, q);
    p /= gcd_val;
    q /= gcd_val;

    ratios[a][b] = {p, q};
    ratios[b][a] = {q, p};
  }
}

void Solve() {
  UnionFind union_find(n);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (ratios[i][j].first == 0)
        continue;

      union_find.Union(i, j, ratios[i][j].first, ratios[i][j].second);
    }
  }

  for (int i = 0; i < n; ++i)
    cout << union_find.GetRatio(i) << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
