#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

struct Interval {
  pair<int, int> from;
  pair<int, int> to;

  bool operator<(const Interval& rhs) const {
    if (to == rhs.to)
      return from > rhs.from;
    return to < rhs.to;
  }
};

int n;
vector<Interval> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 0; i < n; ++i) {
    int start_month, start_day, end_month, end_day;
    cin >> start_month >> start_day >> end_month >> end_day;
    
    if (end_month >= 3)
      arr.push_back({{ start_month, start_day }, { end_month, end_day }});
  }
}

void Solve() {
  sort(arr.begin(), arr.end());

  priority_queue<Interval> pq;
  for (const Interval& interval : arr) {
    //cout << "input: ";
    //cout << interval.from.first  << '.' << interval.from.second << " - ";
    //cout << interval.to.first  << '.' << interval.to.second << '\n';
    if (pq.empty()) {
      pq.push(interval);
      //cout << "push at empty" << endl;
      continue;
    }

    if (pq.top().to < interval.from)
      continue;
    
    while (!pq.empty() && pq.top().from >= interval.from) {
      //cout << "pop by first while" << endl;
      pq.pop();
    }

    if (!pq.empty()) {
      bool push_last = true;
      Interval last;
      do {
        last = pq.top();
        //cout << "top: ";
        //cout << pq.top().from.first  << '.' << pq.top().from.second << " - ";
        //cout << pq.top().to.first  << '.' << pq.top().to.second << '\n';
        pq.pop();

        if (pq.empty() && interval.from <= make_pair(3, 1)) {
          push_last = false;
          break;
        }

        //cout << "pop" << endl;
        //cout << "size: " << ssize(pq) << endl;
      } while (!pq.empty() && pq.top().to >= interval.from);
      
      if (push_last)
        pq.push(last);
    }


    pq.push(interval);
    //cout << "size: " << ssize(pq) << endl;
    //cout << "last top: ";
    //cout << pq.top().from.first  << '.' << pq.top().from.second << " - ";
    //cout << pq.top().to.first  << '.' << pq.top().to.second << '\n';
  }

  //cout << endl;
  if (pq.top().to.first < 12) {
    cout << "0\n";
    //cout << "123";
    return;
  }

  int total = ssize(pq);
  int count1 = 0;
  int count2 = 0;
  while (!pq.empty()) {
    //cout << pq.top().from.first  << '.' << pq.top().from.second << " - ";
    //cout << pq.top().to.first  << '.' << pq.top().to.second << '\n';
    if (pq.top().to.first >= 12)
      ++count1;

    if (pq.top().from <= make_pair(3, 1))
      ++count2;
    pq.pop();
  }

  if (count2 == 0) {
    cout << "0\n";
    //cout << "1234";
    return;
  }

  //cout << "count1: " << count1 << endl;
  //cout << "count2: " << count2 << endl;
  cout << total - (count1 - 1) - (count2 - 1) << endl;



  //cout << pq.size() << '\n';

  /*while (!pq.empty()) {
    cout << pq.top().from.first  << '.' << pq.top().from.second << " - ";
    cout << pq.top().to.first  << '.' << pq.top().to.second << '\n';
    pq.pop();
  }*/
}

int main() {
  GetInput();
  Solve();
  return 0;
}
