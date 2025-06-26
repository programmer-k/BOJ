#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

int n, k;

// 빠른 입출력 설정
void GetInput() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;
}

// 정수 제곱 함수 (Power)
int64_t Power(int base, int exponent) {
    int64_t val = 1;
    for (int i = 0; i < exponent; ++i)
        val *= base;
    return val;
}

void Solve() {
    int digit = 1;               // 현재 자리수 (1자리, 2자리, ...)
    int64_t count = 9;           // 현재 자리수의 숫자 개수
    int64_t length = 0;          // 지금까지 누적된 전체 길이
    int64_t prev_total = 0;      // 이전까지의 누적 길이

    // 자리수 구간 탐색
    while (true) {
        int64_t start = Power(10, digit - 1);
        int64_t end = Power(10, digit) - 1;
        if (start > n) break;

        // 이 자리수에서 실제로 사용할 수 있는 숫자 수
        int64_t last = min((int64_t)n, end);
        int64_t num_count = last - start + 1;
        int64_t add = num_count * digit;

        if (length + add >= k) break;

        length += add;
        ++digit;
    }

    int64_t remain = k - length - 1;  // 0-based 인덱스
    int64_t start = Power(10, digit - 1);
    int64_t offset = remain / digit;
    int64_t pos = remain % digit;
    int64_t target = start + offset;

    if (target > n) {
        cout << -1 << '\n';
        return;
    }

    string s = to_string(target);
    cout << s[pos] << '\n';
}

int main() {
    GetInput();
    Solve();
    return 0;
}