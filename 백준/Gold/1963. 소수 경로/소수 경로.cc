#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int t;
int a, b;
vector<bool> is_prime(10'000, true);

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;
}

void GetInput2() {
  cin >> a >> b;
}

void CalculateFourDigitPrimeNumbers() {
  for (int i = 2; i < 10'000; ++i)
    if (is_prime[i])
      for (int j = i * 2; j < 10'000; j += i)
        is_prime[j] = false;
}

int BreadthFirstSearch() {
  queue<int> q;
  vector<int> visited(10'000, -1);
  q.push(a);
  visited[a] = 0;

  while (!q.empty()) {
    int val = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      string val_str = to_string(val);
      for (int j = 0; j < 10; ++j) {
        val_str[i] = j + '0';

        if (val_str.front() == '0')
          continue;
        
        int next_val = stoi(val_str);
        if (!is_prime[next_val])
          continue;
          
        if (visited[next_val] != -1)
          continue;
        
        q.push(next_val);
        visited[next_val] = visited[val] + 1;
      }
    }
  }

  return visited[b];
}

void Solve() {
  int dist = BreadthFirstSearch();
  if (dist == -1)
    cout << "Impossible\n";
  else
    cout << dist << '\n';
}

int main() {
  CalculateFourDigitPrimeNumbers();
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}