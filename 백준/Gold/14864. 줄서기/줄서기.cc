#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> larger, smaller;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  smaller.resize(n + 1);
  larger.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    ++larger[x];
    ++smaller[y];
  }
}

void Solve() {
  vector<bool> occupied(n + 1);
  vector<int> answers(n + 1);

  for (int i = 1; i <= n; ++i) {
    int large_total = smaller[i] + n - i - larger[i];
    int small_total = larger[i] + i - 1 - smaller[i];
    int total = large_total + small_total;

    if (total != n - 1 || occupied[small_total + 1]) {
      cout << "-1\n";
      return;
    }

    occupied[small_total + 1] = true;
    answers[i] = small_total + 1;
  }

  for (int i = 1; i <= n; ++i)
    cout << answers[i] << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
