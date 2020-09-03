#include <cstdio>

bool f(int n1, int n2, int n3, int n4) {
  if (n1 == 1 || n1 == 2) {
    if (n2 == 0 || n3 == 0) return false;
    if (f(n1 - 1, n2 - 1, n3 - 1, n4)) return true;
    if (n4 > 0 && f(n1 - 1, n2 - 1, n3 - 1, n4 - 1)) return true;
    return false;
  }
  if (n2 == 1 || n2 == 2) {
    if (n3 == 0) return false;
    if (n1 > 0 && n4 > 0 && f(n1 - 1, n2 - 1, n3 - 1, n4 - 1)) return true;
    if (n1 > 0 && f(n1 - 1, n2 - 1, n3 - 1, n4)) return true;
    if (n4 > 0 && f(n1, n2 - 1, n3 - 1, n4 - 1)) return true;
    return false;
  }
  if (n3 == 1 || n3 == 2) return f(n1, n3, n2, n4);
  if (n4 == 1 || n4 == 2) return f(n4, n2, n3, n1);
  return true;
}

int main() {
  int T;
  for (scanf("%d", &T); T-- > 0; ) {
    int n1, n2, n3, n4;
    scanf("%d%d%d%d", &n1, &n2, &n3, &n4);
    puts(f(n1, n2, n3, n4) ? "Yes" : "No");
  }
  return 0;
}
