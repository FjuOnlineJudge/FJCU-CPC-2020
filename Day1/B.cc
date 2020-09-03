#include <cstdio>
#include <cstring>

char S[2000001];

int main() {
  int Q;
  scanf("%s%d", S, &Q);
  int N = strlen(S);
  for (int o = 0; Q-- > 0; ) {
    char c; int x;
    scanf(" %c%d", &c, &x);
    if (c == 'M') {
      o = (o + N + x) % N;
    } else {
      putchar(S[(o + x - 1) % N]);
      putchar('\n');
    }
  }
  return 0;
}
