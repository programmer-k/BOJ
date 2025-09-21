#include <iostream>
#include <vector>
using namespace std;

int m, n;
vector<vector<int>> arr(1'000'000, vector<int>(3));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> m >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < 3; ++j)
      cin >> arr[i][j];
}

void Solve() {
  vector<int> answers(2 * m - 1, 1);
  for (int i = 0; i < n; ++i) {
    int index = 0;
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < arr[i][j]; ++k) {
        answers[index++] += j;
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j == 0) {
        cout << answers[m - i - 1] << ' ';
      } else {
        cout << answers[m + j - 1] << ' ';
      }
    }
    cout << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
