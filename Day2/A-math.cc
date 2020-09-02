#include <cstdio>

int main() {
  int a, b;
  scanf("%d%d", &a, &b);
  int k = 0;
  for (; a < b; a <<= 1) k++;
  a -= b;
  for (int c = 1 << k; c > 0; c >>= 1) {
    k += a / c;
    a %= c;
  }
  printf("%d\n", k);
  return 0;
}
