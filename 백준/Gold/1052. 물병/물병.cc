#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, k;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
}

/*int CalcMinBottleToBuy(int bottle, int bottle_to_buy, vector<int>& remainders, int remainders_total) {
  cout << "CalcMinBottleToBuy(" << bottle << ")" << endl;
  int quotient = bottle / 2;
  int remainder = bottle % 2;
  remainders.push_back(remainder);
  remainders_total += remainder;

  if (quotient + remainders_total <= k) {
    return bottle_to_buy;
  }

  if (quotient == 0) {
    for (int i = 0; i < ssize(remainders); ++i) {

    }
  }

  CalcMinBottleToBuy(quotient, bottle_to_buy, remainders, remainders_total);
}*/

void Solve() {
  //vector<int> remainders;
  //cout << CalcMinBottleToBuy(n, 0, remainders, 0) << '\n';

  int power_of_two = 8388608;
  priority_queue<int, vector<int>, greater<int>> pq;
  while (power_of_two) {
    if (n - power_of_two >= 0) {
      n -= power_of_two;
      pq.push(power_of_two);
    }
    
    power_of_two /= 2;
  }

  int bottle = 0;
  while (ssize(pq) > k) {
    int val1 = pq.top();
    pq.pop();

    int val2 = pq.top();
    pq.pop();

    bottle += val2 - val1;
    pq.push(val2 * 2);
  }
  cout << bottle << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}