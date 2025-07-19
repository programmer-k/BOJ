#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int n, m;
array<int, 50> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  int answer = 0;
  vector<int> positives, negatives;

  for (int i = 0; i < n; ++i)
    arr[i] > 0 ? positives.push_back(arr[i]) : negatives.push_back(-arr[i]);

  sort(positives.begin(), positives.end(), greater<int>());
  sort(negatives.begin(), negatives.end(), greater<int>());

  for (int i = 0; i < ssize(positives); i += m) {
    answer += positives[i] * 2;
  }

  for (int i = 0; i < ssize(negatives); i += m) {
    answer += negatives[i] * 2;
  }

  if (ssize(positives) == 0)
    answer -= negatives.front();
  else if (ssize(negatives) == 0)
    answer -= positives.front();
  else if (positives.front() > negatives.front())
    answer -= positives.front();
  else
    answer -= negatives.front();

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}