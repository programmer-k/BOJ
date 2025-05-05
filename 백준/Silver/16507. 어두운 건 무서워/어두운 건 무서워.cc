#include <iostream>
#include <array>
#include <vector>
using namespace std;

struct Rect {
  int r1;
  int c1;
  int r2;
  int c2;
};

int r, c, q;
array<array<int, 1'001>, 1'001> map;
vector<vector<int>> sum(1'001, vector<int>(1'001));
array<Rect, 10'000> rects;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> r >> c >> q;
  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= c; ++j)
      cin >> map[i][j];
  
  for (int i = 0; i < q; ++i)
    cin >> rects[i].r1 >> rects[i].c1 >> rects[i].r2 >> rects[i].c2;
}

void Solve() {
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + map[i][j];
    }
  }



  for (int i = 0; i < q; ++i) {
    int r1 = rects[i].r1;
    int c1 = rects[i].c1;
    int r2 = rects[i].r2;
    int c2 = rects[i].c2;

    int rect1 = sum[r2][c2];
    int rect2 = sum[r2][c1 - 1];
    int rect3 = sum[r1 - 1][c2];
    int rect4 = sum[r1 - 1][c1 - 1];
    int total = rect1 - rect2 - rect3 + rect4;
    int size = (r2 - r1 + 1) * (c2 - c1 + 1);
    cout << total / size << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}