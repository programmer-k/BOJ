#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Brick {
  int area;
  int height;
  int weight;
  int index;

  bool operator<(const Brick& rhs) const {
    return area < rhs.area;
  }

  bool operator>(const Brick& rhs) const {
    return rhs < *this;
  }
};

int n;
vector<Brick> bricks;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int area, height, weight;
    cin >> area >> height >> weight;
    bricks.push_back({area, height, weight, i + 1});
  }
}

void Solve() {
  sort(bricks.begin(), bricks.end(), greater<Brick>());

  vector<pair<int, int>> dp(n);
  for (int i = 0; i < n; ++i) {
    dp[i].first = bricks[i].height;
    dp[i].second = -1;
    for (int j = 0; j < i; ++j) {
      if (bricks[i].weight < bricks[j].weight &&
          dp[i].first < dp[j].first + bricks[i].height) {
        dp[i].first = dp[j].first + bricks[i].height;
        dp[i].second = j;
      }
    }
  }

  int count = 0;
  vector<int> answers;
  int index = max_element(dp.begin(), dp.end()) - dp.begin();
  while (index != -1) {
    answers.push_back(bricks[index].index);
    ++count;
    index = dp[index].second;
  }

  cout << count << '\n';
  for (int answer : answers)
    cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
