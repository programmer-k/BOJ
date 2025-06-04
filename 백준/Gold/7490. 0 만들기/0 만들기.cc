#include <stdio.h>

int tc;
int n;
char expression[18] = "11223344556677889";

void GetInput1() {
  scanf("%d", &tc);
}

void GetInput2() {
  scanf("%d", &n);
}

void FindAllZeroExpressions(int index, int val) {
  if (index == n - 1) {
    int total = 0;
    int temp = 1;
    for (int i = 1; i < n * 2 - 1; i += 2) {
      int val = expression[i + 1] - '0';
      if (expression[i] == '+') {
        total += temp;
        temp = val;
      } else if (expression[i] == '-') {
        total += temp;
        temp = -val;
      } else {
        temp *= 10;
        if (temp < 0)
          temp -= val;
        else
          temp += val;
      }
    }
    total += temp;
    if (total == 0) {
      for (int i = 0; i < n * 2 - 1; ++i)
        printf("%c", expression[i]);
      printf("\n");
    }
    return;
  }

  expression[index * 2 + 1] = ' ';
  FindAllZeroExpressions(index + 1, 0);
  expression[index * 2 + 1] = '+';
  FindAllZeroExpressions(index + 1, 0);
  expression[index * 2 + 1] = '-';
  FindAllZeroExpressions(index + 1, 0);
}

void Solve() {
  FindAllZeroExpressions(0, 1);
  printf("\n");
}

int main(void) {
  GetInput1();
  for (int i = 0; i < tc; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}