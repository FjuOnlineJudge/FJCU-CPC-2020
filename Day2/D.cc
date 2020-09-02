#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int NMAX = 300000;
const int MMAX = 300000;

int N, M, S;
vector<int> F[NMAX];
vector<int> E[NMAX];
int edge[MMAX][3];

void solve(bool flag) {
  static bool marked[NMAX];
  memset(marked, 0, sizeof(marked));
  for (int i = 0; i < M; i++) edge[i][2] = '?';
  vector<int> colle;
  colle.push_back(S);
  marked[S] = true;
  int c = 0;
  while (!colle.empty()) {
    c++;
    auto u = colle.back();
    colle.pop_back();
    for (auto v : F[u]) {
      if (!marked[v]) { colle.push_back(v); marked[v] = true; }
    }
    for (auto i : E[u]) {
      auto f = edge[i][0] == u;
      if (flag) {
        auto v = edge[i][f ? 1 : 0];
        if (!marked[v]) {
          colle.push_back(v);
          marked[v] = true;
          edge[i][2] = f ? '+' : '-';
        }
      } else {
        if (edge[i][2] == '?') {
          edge[i][2] = f ? '-' : '+';
        }
      }
    }
  }
  printf("%d\n", c);
  for (int i = 0; i < M; i++) putchar(edge[i][2] == '+' ? '+' : '-');
  putchar('\n');
}

int main() {
  scanf("%d%d%d", &N, &M, &S); S--;
  int m = 0;
  for (int i = 0; i < M; i++) {
    int c, a, b;
    scanf("%d%d%d", &c, &a, &b); a--; b--;
    if (c == 1) {
      F[a].push_back(b);
    } else {
      E[a].push_back(m);
      E[b].push_back(m);
      edge[m][0] = a;
      edge[m][1] = b;
      m++;
    }
  }
  M = m;
  solve(true);
  solve(false);
  return 0;
}
