#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct Delivery {
  int from;
  int to;
  int box_count;

  // [수정 1] 받는 마을(to)을 기준으로 오름차순 정렬해야 최적해를 보장합니다.
  // 받는 마을이 같다면 보내는 마을(from) 순으로 정렬합니다.
  bool operator<(const Delivery& rhs) const {
    if (to != rhs.to) return to < rhs.to;
    return from < rhs.from;
  }
};

int n, c, m;
Delivery deliveries[10000];
// [수정 2] 각 마을 위치(구간)별로 현재 트럭에 실려있는 짐의 양을 저장하는 배열입니다.
int truck_load[2001]; 

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> c;
  cin >> m;

  for (int i = 0; i < m; ++i)
    cin >> deliveries[i].from >> deliveries[i].to >> deliveries[i].box_count;
}

void Solve() {
  // 받는 마을 순서로 정렬
  sort(deliveries, deliveries + m);

  int total_box_count = 0;

  for (int i = 0; i < m; ++i) {
    int from = deliveries[i].from;
    int to = deliveries[i].to;
    int box_count = deliveries[i].box_count;

    // 1. 현재 배송할 구간(from ~ to-1)에서 트럭에 가장 짐이 많이 실린 양(max_load)을 찾습니다.
    // to에 도착하면 내리므로 to-1까지만 확인합니다.
    int max_load_on_path = 0;
    for (int j = from; j < to; ++j) {
      if (truck_load[j] > max_load_on_path) {
        max_load_on_path = truck_load[j];
      }
    }

    // 2. 현재 배송 건을 얼마나 더 실을 수 있는지 계산합니다.
    // (트럭 용량 - 구간 내 최대 적재량) 과 (보내려는 박스 수) 중 작은 값
    int can_load = min(box_count, c - max_load_on_path);

    // 3. 실을 수 있는 만큼 싣고, 결과에 더합니다.
    if (can_load > 0) {
      total_box_count += can_load;
      
      // 해당 구간의 트럭 적재량을 갱신합니다.
      for (int j = from; j < to; ++j) {
        truck_load[j] += can_load;
      }
    }
  }

  cout << total_box_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}