#include <cassert>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int NMAX = 10000;
const int INF = 2000000000;

struct edge {
  int a, b, d, z;
  edge(int a, int b, int d, int z) : a(a), b(b), d(d), z(z) { }
  bool operator<(const edge &that) const { return z > that.z; }
};

struct item {
  int u, d;
  item(int u, int d) : u(u), d(d) { }
  bool operator<(const item &that) const { return d > that.d; }
};

int N, K;
vector<edge> edges;
int boz[NMAX];
int siz[NMAX];
vector<pair<int, int>> E[NMAX];
int D[NMAX];

void Dijkstra() {
  priority_queue<item> Q;
  for (int i = 0; i < N; i++) D[i] = INF;
  D[N - 1] = 0;
  Q.emplace(N - 1, 0);
  while (!Q.empty()) {
    auto top = Q.top();
    Q.pop();
    if (D[top.u] != top.d) continue;
    for (auto e : E[top.u]) {
      auto v = e.first;
      auto d = top.d + e.second;
      if (d < D[v]) {
        D[v] = d;
        Q.emplace(v, d);
      }
    }
  }
}

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
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    int m;
    scanf("%d%d%d", &N, &K, &m);
    while (m-- > 0) {
      int a, b, d, z;
      scanf("%d%d%d%d", &a, &b, &d, &z); a--; b--;
      edges.emplace_back(a, b, d, z);
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < N; i++) boz[i] = i;
    for (int i = 0; i < N; i++) siz[i] = 1;
    for (int i = 1; i < K; i++) Union(0, i);
    int P = 0;
    for (auto e : edges) {
      if (P == 0) {
        Union(e.a, e.b);
        if (Find(0) == Find(N - 1)) P = e.z;
      } else if (e.z < P) {
        break;
      }
      E[e.a].emplace_back(e.b, e.d);
      E[e.b].emplace_back(e.a, e.d);
    }
    assert(P > 0);
    edges.clear();
    Dijkstra();
    for (int i = 0; i < N; i++) { E[i].clear(); E[i].shrink_to_fit(); }
    auto mind = *min_element(D, D + K);
    printf("Case #%d:", t);
    for (int i = 0; i < K; i++) if (D[i] == mind) printf(" %d", i + 1);
    putchar('\n');
  }
  return 0;
}
