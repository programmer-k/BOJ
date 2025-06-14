#include <iostream>
#include <algorithm>
#include <utility>
#include <array>
#include <queue>
#include <vector>
using namespace std;

int n;
array<pair<int, int>, 100'000> lectures;
priority_queue<int, vector<int>, greater<int>> pq;

void GetInput() {
  int temp;
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> temp >> lectures[i].first >> lectures[i].second;
}

void Solve() {
  sort(lectures.begin(), lectures.begin() + n);

  pq.push(lectures[0].second);
  for (int i = 1; i < n; ++i) {
    pair<int, int> lecture = lectures[i];

    if (lecture.first < pq.top()) {
      pq.push(lecture.second);
    } else {
      pq.pop();
      pq.push(lecture.second);
    }
  }

  cout << pq.size() << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}