#include <iostream>
#include <array>
#include <set>
using namespace std;

int a, b, c;
set<int> possible_fills;
array<array<array<int, 201>, 201>, 201> visited;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c;
}

void DepthFirstSearch(int a_filled, int b_filled, int c_filled) {
  if (visited[a_filled][b_filled][c_filled])
    return;
  
  visited[a_filled][b_filled][c_filled] = true;

  if (a_filled == 0)
    possible_fills.insert(c_filled);
  
  // From a
  DepthFirstSearch(a_filled - (min(a_filled + b_filled, b) - b_filled), min(a_filled + b_filled, b), c_filled);
  DepthFirstSearch(a_filled - (min(a_filled + c_filled, c) - c_filled), b_filled, min(a_filled + c_filled, c));

  // From b
  DepthFirstSearch(min(a_filled + b_filled, a), b_filled - (min(a_filled + b_filled, a) - a_filled), c_filled);
  DepthFirstSearch(a_filled, b_filled - (min(b_filled + c_filled, c) - c_filled), min(b_filled + c_filled, c));

  // From c
  DepthFirstSearch(min(a_filled + c_filled, a), b_filled, c_filled - (min(a_filled + c_filled, a) - a_filled));
  DepthFirstSearch(a_filled, min(b_filled + c_filled, b), c_filled - (min(b_filled + c_filled, b) - b_filled));
}

void Solve() {
  DepthFirstSearch(0, 0, c);
  for (int fill : possible_fills)
    cout << fill << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}