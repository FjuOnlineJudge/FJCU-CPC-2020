#include <cstdio>
#include <algorithm>
using namespace std;

const int NMAX = 500000;

int boz[NMAX];
int siz[NMAX];

int Find(int x) {
  while (boz[x] != x) x = boz[x];
  return x;
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (a == b) return;
  if (siz[a] < siz[b]) swap(a, b);
  boz[b] = a;
  siz[a] += siz[b];
}

int main() {
  int N, g;
  scanf("%d%d", &N, &g);
  for (int i = 0; i < N; i++) { boz[i] = i; siz[i] = 1; }
  while (g-- > 0) {
    int n, a;
    scanf("%d", &n);
    if (n == 0) continue;
    scanf("%d", &a); a--;
    for (int i = 1; i < n; i++) {
      int b;
      scanf("%d", &b); b--;
      Union(a, b);
    }
  }
  for (int i = 0; i < N; i++) {
    if (i > 0) putchar(' ');
    printf("%d", siz[Find(i)]);
  }
  putchar('\n');
  return 0;
}
