#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int k;
vector<pair<int, int>> nodes;

int Power(int base, int exponent) {
  int result = 1;
  for (int i = 0; i < exponent; ++i)
    result *= base;
  return result;
}

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> k;

  nodes.resize(Power(2, k));
  for (int i = 1; i < ssize(nodes); ++i)
    cin >> nodes[i].first >> nodes[i].second;
}

int UpdateEdgesWeight(int node) {
  if (node >= ssize(nodes))
    return 0;

  int child1 = UpdateEdgesWeight(node * 2) + nodes[node].first;
  int child2 = UpdateEdgesWeight(node * 2 + 1) + nodes[node].second;

  if (child1 > child2) {
    nodes[node].second += child1 - child2;
  } else if (child1 < child2) {
    nodes[node].first += child2 - child1;
  }

  return max(child1, child2);
}

int CalculateTotalWeight(int node) {
  if (node >= ssize(nodes))
    return 0;

  int child1 = CalculateTotalWeight(node * 2) + nodes[node].first;
  int child2 = CalculateTotalWeight(node * 2 + 1) + nodes[node].second;

  return child1 + child2;
}

void Solve() {
  UpdateEdgesWeight(1);
  cout << CalculateTotalWeight(1) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
