#include <stdio.h>

int arr[101];

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  
  for (int i = 0; i < m; ++i) {
    int from, to, ball_num;
    scanf("%d %d %d", &from, &to, &ball_num);

    for (int j = from; j <= to; ++j)
      arr[j] = ball_num;
  }

  for (int i = 1; i <= n; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}