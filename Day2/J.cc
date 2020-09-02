#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int NMAX = 100000;

int N, M;
bool cat[NMAX];
vector<int> E[NMAX];

int dfs(int u, int p, int c) {
  if (!cat[u]) {
    c = 0;
  } else if (++c > M) {
    return 0;
  }
  if (E[u].size() == 1 && p >= 0) return 1;
  int ret = 0;
  for (auto v : E[u]) {
    if (v == p) continue;
    ret += dfs(v, u, c);
  }
  return ret;
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    cat[i] = x != 0;
  }
  for (int i = 1; i < N; i++) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--;
    E[a].push_back(b);
    E[b].push_back(a);
  }
  printf("%d\n", dfs(0, -1, 0));
  return 0;
}
