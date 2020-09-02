#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int NMAX = 2000;

int N;
vector<int> E[1 + NMAX];

int dfs(int u) {
  int res = 0;
  for (auto v : E[u]) res = max(res, dfs(v));
  return res + 1;
}

int main() {
  scanf("%d", &N);
  for (int u = 1; u <= N; u++) {
    int p;
    scanf("%d", &p);
    E[max(p, 0)].push_back(u);
  }
  printf("%d\n", dfs(0) - 1);
  return 0;
}
