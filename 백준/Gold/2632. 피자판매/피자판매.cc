#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

const int kMillion = 1'000'000;

int pizza_size, m, n;
vector<int> pizza1, pizza2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> pizza_size;
  cin >> m >> n;

  pizza1.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> pizza1[i];

  pizza2.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> pizza2[i];
}

void CountContiguousSubArraySum(const vector<int>& arr, int length,
                                vector<int>& sum_counts) {
  int sum = 0;
  for (int i = 0; i < length; ++i)
    sum += arr[i];

  if (ssize(arr) == length) {
    ++sum_counts[sum];
    return;
  }

  for (int i = 0; i < ssize(arr); ++i) {
    sum -= arr[i];
    sum += arr[(i + length) % ssize(arr)];
    ++sum_counts[sum];
  }
}

void Solve() {
  vector<int> sum_counts1(kMillion + 1), sum_counts2(kMillion + 1);
  for (int i = 1; i <= ssize(pizza1); ++i)
    CountContiguousSubArraySum(pizza1, i, sum_counts1);

  for (int i = 1; i <= ssize(pizza2); ++i)
    CountContiguousSubArraySum(pizza2, i, sum_counts2);

  int64_t answer = 0;
  sum_counts1[0] = 1;
  sum_counts2[0] = 1;
  for (int i = 0; i <= pizza_size; ++i)
    if (i <= kMillion && pizza_size - i <= kMillion)
      answer +=
          static_cast<int64_t>(sum_counts1[i]) * sum_counts2[pizza_size - i];

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
