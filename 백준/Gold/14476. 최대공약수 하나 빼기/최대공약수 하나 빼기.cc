#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int n;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void UpdateAnswer(int new_gcd, int new_index, int& curr_gcd, int& curr_index) {
  if (new_gcd > curr_gcd) {
    curr_gcd = new_gcd;
    curr_index = new_index;
  }
}

void Solve() {
  vector<int> forward_gcds(n), backward_gcds(n);

  forward_gcds[0] = arr[0];
  for (int i = 1; i < n; ++i)
    forward_gcds[i] = gcd(forward_gcds[i - 1], arr[i]);

  backward_gcds[n - 1] = arr[n - 1];
  for (int i = n - 2; i >= 0; --i)
    backward_gcds[i] = gcd(backward_gcds[i + 1], arr[i]);

  int answer_gcd = -1;
  int answer_index = -1;
  if (arr[0] % backward_gcds[1] != 0)
    UpdateAnswer(backward_gcds[1], 0, answer_gcd, answer_index);

  if (arr[n - 1] % forward_gcds[n - 2] != 0)
    UpdateAnswer(forward_gcds[n - 2], n - 1, answer_gcd, answer_index);

  for (int i = 1; i < n - 1; ++i) {
    int final_gcd = gcd(forward_gcds[i - 1], backward_gcds[i + 1]);
    if (arr[i] % final_gcd != 0)
      UpdateAnswer(final_gcd, i, answer_gcd, answer_index);
  }

  if (answer_gcd == -1)
    cout << "-1\n";
  else
    cout << answer_gcd << ' ' << arr[answer_index] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
