#include <iostream>
#include <array>
#include <cstdint>
#include <vector>
using namespace std;

int n, problem_num;
int64_t k;
array<int, 20> arr;
array<int64_t, 21> factorials;
array<bool, 21> in_use;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  cin >> problem_num;
  
  if (problem_num == 1)
    cin >> k;
  else
    for (int i = 0; i < n; ++i)
      cin >> arr[i];
}

int GetNthNum(int n) {
  int count = 0;
  for (int i = 1; i <= 20; ++i) {
    if (!in_use[i]) {
      ++count;

      if (count == n) {
        in_use[i] = true;
        return i;
      }
    }
  }

  return -1;
}

void FindPermutation(int n, int64_t k, vector<int>& answer) {
  if (n == 0)
    return;

  int64_t each_case = factorials[n - 1];
  int quotient = k / each_case;
  int64_t remainder = k % each_case;
  
  int selected_num = GetNthNum(quotient + 1);
  answer.push_back(selected_num);

  FindPermutation(n - 1, remainder, answer);
}

int GetNumOrder(int num) {
  int count = 0;
  in_use[num] = true;
  for (int i = 1; i <= num; ++i) {
    if (!in_use[i]) {
      ++count;
    }
  }
  return count;
}

int64_t FindPermutationOrder(int index, int64_t permutation_index) {
  if (index == n)
    return permutation_index;

  int num_order = GetNumOrder(arr[index]);
  int64_t curr_permuation_index = num_order * factorials[n - index - 1];
  return FindPermutationOrder(index + 1, permutation_index + curr_permuation_index);
}

void Solve() {
  factorials[0] = factorials[1] = 1;
  for (int i = 2; i <= 20; ++i)
    factorials[i] = factorials[i - 1] * i;

  if (problem_num == 1) {
    vector<int> answer;
    FindPermutation(n, k - 1, answer);

    for (int val : answer)
      cout << val << ' ';
    cout << '\n';
  } else {
    cout << FindPermutationOrder(0, 0) + 1 << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}