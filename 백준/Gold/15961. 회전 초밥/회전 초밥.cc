#include <iostream>
#include <vector>
using namespace std;

int n, d, k, c;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  
  cin >> n >> d >> k >> c;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  int max_count = 0;
  int count = 0;
  vector<int> counts(d + 1);
  
  for (int i = 0; i < k; ++i)
    if (counts[arr[i]]++ == 0)
      ++count;

  for (int i = 0; i < n; ++i) {
    if (counts[c] == 0)
      max_count = max(max_count, count + 1);
    else
      max_count = max(max_count, count);

    if (--counts[arr[i]] == 0)
      --count;
    
    if (counts[arr[(i + k) % n]]++ == 0)
      ++count;
  }

  cout << max_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
