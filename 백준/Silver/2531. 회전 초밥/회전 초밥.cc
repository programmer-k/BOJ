#include <iostream>
#include <set>
#include <map>
using namespace std;

int n, d, k, c;
int sushi[32998];
map<int, int> selected_sushi;
int max_size;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> d >> k >> c;
  for (int i = 0; i < n; ++i)
    cin >> sushi[i];
}

void UpdateMaxSize() {
  int size = selected_sushi.size();
  if (selected_sushi.find(c) != selected_sushi.end())
    max_size = max(max_size, size);
  else
    max_size = max(max_size, size + 1);
}

void Solve() {
  for (int i = n; i < n + k - 1; ++i)
    sushi[i] = sushi[i - n];

  for (int i = 0; i < k; ++i)
    ++selected_sushi[sushi[i]];
  UpdateMaxSize();

  for (int i = k; i < n + k - 1; ++i) {
    if (--selected_sushi[sushi[i - k]] == 0)
      selected_sushi.erase(sushi[i - k]);
    ++selected_sushi[sushi[i]];
    UpdateMaxSize();
  }

  cout << max_size << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}