#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int NMAX = 200000;

vector<int> A[2];
int boz[NMAX];
int siz[NMAX];
vector<int> E[NMAX];

int Find(int x) {
  while (boz[x] != x) x = boz[x];
  return x;
}

bool Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (a == b) return false;
  if (siz[a] < siz[b]) swap(a, b);
  boz[b] = a;
  siz[a] += siz[b];
  return true;
}

void dfs(int u, int p, int x) {
  A[x].push_back(u + 1);
  for (auto v : E[u]) {
    if (v == p) continue;
    dfs(v, u, x ^ 1);
  }
}

int main() {
  int T;
  for (scanf("%d", &T); T-- > 0; ) {
    int N, m;
    scanf("%d%d", &N, &m);
    for (int i = 0; i < N; i++) { boz[i] = i; siz[i] = 1; }
    while (m-- > 0) {
      int a, b;
      scanf("%d%d", &a, &b); a--; b--;
      if (Union(a, b)) {
        E[a].push_back(b);
        E[b].push_back(a);
      }
    }
    dfs(0, -1, 0);
    if (A[0].size() > A[1].size()) swap(A[0], A[1]);
    printf("%d\n%d", (int)A[0].size(), A[0][0]);
    for (int i = 1; i < (int)A[0].size(); i++) printf(" %d", A[0][i]);
    putchar('\n');
    for (int i = 0; i < 2; i++) A[i].clear();
    for (int i = 0; i < N; i++) { E[i].clear(); E[i].shrink_to_fit(); }
  }
  return 0;
}
