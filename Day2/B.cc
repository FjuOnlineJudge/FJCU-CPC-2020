#include <cstdio>

const int NMAX = 10000;

int P[1 + NMAX];
int C[1 + NMAX];

int main() {
  int N;
  scanf("%d", &N);
  for (int i = 2; i <= N; i++) scanf("%d", P + i);
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    scanf("%d", C + i);
    if (C[i] != C[P[i]]) ans++;
  }
  printf("%d\n", ans);
  return 0;
}
