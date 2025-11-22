#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, k;
vector<string> nums;
vector<vector<int>> num_counts(36, vector<int>(50));
vector<vector<int>> num_benefits(36, vector<int>(51));
vector<int> total(100);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  nums.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> nums[i];

  cin >> k;
}

int GetIndex(char ch) {
  if (ch >= '0' && ch <= '9')
    return ch - '0';
  return ch - 'A' + 10;
}

char GetChar(int index) {
  if (index < 10)
    return '0' + index;
  return 'A' + index - 10;
}

void CountNums() {
  for (string& num : nums) {
    reverse(num.begin(), num.end());
    for (int i = 0; i < ssize(num); ++i) {
      char ch = num[i];
      ++num_counts[GetIndex(ch)][i];
    }
  }
}

void CalculateBenefits() {
  for (int i = 0; i < 36; ++i) {
    int diff = GetIndex('Z') - i;
    for (int j = 0; j < 50; ++j) {
      int count = num_counts[i][j];
      num_benefits[i][j] += diff * count;
      num_benefits[i][j + 1] = num_benefits[i][j] / 36;
      num_benefits[i][j] %= 36;
    }
  }
}

void SortBenefits() {
  for (int i = 0; i < 36; ++i)
    reverse(num_benefits[i].begin(), num_benefits[i].end());

  sort(num_benefits.begin(), num_benefits.end(), greater<vector<int>>());

  for (int i = 0; i < 36; ++i)
    reverse(num_benefits[i].begin(), num_benefits[i].end());
}

void AddAll() {
  for (const string& num : nums) {
    for (int i = 0; i < ssize(num); ++i) {
      char ch = num[i];
      total[i] += GetIndex(ch);
      total[i + 1] += total[i] / 36;
      total[i] %= 36;
    }
  }

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < ssize(num_benefits[i]); ++j) {
      total[j] += num_benefits[i][j];
      total[j + 1] += total[j] / 36;
      total[j] %= 36;
    }
  }

  for (int i = 0; i < ssize(total) - 1; ++i) {
    total[i + 1] += total[i] / 36;
    total[i] %= 36;
  }
}

string ConvertIntToChar() {
  string answer(total.size(), '0');
  for (int i = 0; i < ssize(total); ++i)
    answer[i] = GetChar(total[i]);

  reverse(answer.begin(), answer.end());
  size_t answer_start = answer.find_first_not_of('0');
  if (answer_start != string::npos)
    return answer.substr(answer_start);
  return "0";
}

void Solve() {
  CountNums();
  CalculateBenefits();
  SortBenefits();
  AddAll();
  cout << ConvertIntToChar() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
