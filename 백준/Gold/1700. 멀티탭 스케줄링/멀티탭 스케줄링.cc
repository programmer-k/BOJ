#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  
  vector<int> devices(k);
  for (int i = 0; i < k; i++) {
    cin >> devices[i];
  }
  
  set<int> plugged;  // 현재 멀티탭에 꽂혀있는 기기들
  int unplugCount = 0;  // 플러그를 빼는 횟수
  
  for (int i = 0; i < k; i++) {
    int currentDevice = devices[i];
    
    // 이미 꽂혀있으면 그냥 진행
    if (plugged.count(currentDevice)) {
      continue;
    }
    
    // 멀티탭에 빈 자리가 있으면 꽂기
    if (plugged.size() < n) {
      plugged.insert(currentDevice);
      continue;
    }
    
    // 멀티탭이 가득 찼고, 현재 기기가 없다면
    // 이후에 가장 늦게 다시 사용될 기기를 찾아서 제거
    int toRemove = -1;
    int maxLastUsed = -1;
    
    for (int device : plugged) {
      // device의 다음 사용 시점을 찾기
      int lastUsed = k;  // 사용하지 않으면 k로 설정
      for (int j = i + 1; j < k; j++) {
        if (devices[j] == device) {
          lastUsed = j;
          break;
        }
      }
      
      // 가장 늦게 사용되는 기기를 찾기
      if (lastUsed > maxLastUsed) {
        maxLastUsed = lastUsed;
        toRemove = device;
      }
    }
    
    // 가장 늦게 사용될 기기를 제거하고 현재 기기를 꽂기
    plugged.erase(toRemove);
    plugged.insert(currentDevice);
    unplugCount++;
  }
  
  cout << unplugCount << endl;
  
  return 0;
}
