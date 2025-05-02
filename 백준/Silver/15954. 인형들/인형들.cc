#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int n, k;
vector<int> arr(500);


void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

double CalcStandardDeviation(int from, int to, int len) {
  int total = 0;
  for (int i = from; i <= to; ++i) {
    total += arr[i];
  }

  double average = (double) total / len;
  double variance = 0;
  for (int i = from; i <= to; ++i) {
    variance += pow((arr[i] - average), 2);
  }
  variance /= len;
  return sqrt(variance);
}

void Solve() {
  double answer = 1234567890;
  for (int i = 0; i < n; ++i) {
    for (int j = i + k - 1; j < n; ++j) {
      answer = min(answer, CalcStandardDeviation(i, j, j - i + 1));
    }
  }

  cout << fixed << setprecision(11) << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}