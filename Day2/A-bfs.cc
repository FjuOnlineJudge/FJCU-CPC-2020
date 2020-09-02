#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAX = 10000;

deque<int> Q;
int D[MAX * 2];

void update(int v, int d) {
  if (0 < v && v < MAX * 2 && D[v] < 0) {
    D[v] = d;
    Q.push_back(v);
  }
}

int main() {
  memset(D, 0xFF, sizeof(D));
  int a, b;
  scanf("%d%d", &a, &b);
  D[a] = 0;
  Q.push_back(a);
  while (D[b] < 0) {
    auto u = Q.front();
    Q.pop_front();
    update(u * 2, D[u] + 1);
    update(u - 1, D[u] + 1);
  }
  printf("%d\n", D[b]);
  return 0;
}
