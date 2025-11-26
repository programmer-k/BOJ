#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Cashier {
  int cashier_id;
  int time;
  int customer_id;

  bool operator<(const Cashier& rhs) const {
    if (this->time != rhs.time)
      return this->time < rhs.time;
    return this->cashier_id < rhs.cashier_id;
  }

  bool operator>(const Cashier& rhs) const {
    return rhs < *this;
  }
};

struct Exit {
  int cashier_id;
  int time;
  int customer_id;

  Exit(const Cashier& cashier)
      : cashier_id(cashier.cashier_id),
        time(cashier.time),
        customer_id(cashier.customer_id) {
  }

  bool operator<(const Exit& rhs) const {
    if (this->time != rhs.time)
      return this->time < rhs.time;
    return this->cashier_id > rhs.cashier_id;
  }

  bool operator>(const Exit& rhs) const {
    return rhs < *this;
  }
};

int n, k;
vector<pair<int, int>> customers;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> k;

  customers.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> customers[i].first >> customers[i].second;
}

void Solve() {
  priority_queue<Cashier, vector<Cashier>, greater<Cashier>> pq;
  priority_queue<Exit, vector<Exit>, greater<Exit>> answers;
  for (int i = 1; i <= k; ++i)
    pq.push({i, 0, -1});

  for (int i = 0; i < n; ++i) {
    Cashier cashier = pq.top();
    pq.pop();

    if (cashier.customer_id != -1)
      answers.push(cashier);

    cashier.time += customers[i].second;
    cashier.customer_id = customers[i].first;
    pq.push(cashier);
  }

  while (!pq.empty()) {
    Cashier cashier = pq.top();
    pq.pop();

    if (cashier.customer_id != -1)
      answers.push(cashier);
  }

  int64_t total = 0;
  for (int i = 1; i <= n; ++i) {
    Exit exit = answers.top();
    answers.pop();

    total += static_cast<int64_t>(exit.customer_id) * i;
  }

  cout << total << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
