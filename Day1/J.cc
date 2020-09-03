#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

const int NMAX = 20;

struct state {
  int dep, sum; ll msk;
  state(int d, int s, ll m) : dep(d), sum(s), msk(m) { }
  bool operator<(const state &that) const { return sum > that.sum; }
};

struct edge {
  int c, a, b;
  edge(int c, int a, int b) : c(c), a(a), b(b) { }
  bool operator<(const edge &that) const { return c < that.c; }
};

int N, M;
priority_queue<state> H;
vector<edge> E;

static inline bool get(ll x, int i) {
  return ((x >> i) & 1) != 0;
}

static inline ll set(ll x, int i) {
  return x | ((ll)1 << i);
}

int main() {
  int K;
  scanf("%d%d%d", &N, &M, &K);
  if (--K == 0) { puts("0"); return 0; }
  for (int i = 0; i < M; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c); a--; b--;
    E.emplace_back(c, a, b);
  }
  sort(E.begin(), E.end());
  auto next = [&] (int dep, ll msk) {
    for (; dep < M; dep++) {
      if (!get(msk, E[dep].a) && !get(msk, N + E[dep].b)) break;
    }
    return dep;
  };
  H.emplace(0, E[0].c, 0);
  for (; ; ) {
    auto u = H.top();
    if (--K == 0) { printf("%d\n", u.sum); break; }
    H.pop();
    auto t = next(u.dep + 1, u.msk);
    if (t < M) {
      H.emplace(t, u.sum + E[t].c - E[u.dep].c, u.msk);
      auto m = set(set(u.msk, E[u.dep].a), N + E[u.dep].b);
      t = next(u.dep + 1, m);
      if (t < M) H.emplace(t, u.sum + E[t].c, m);
    }
  }
  return 0;
}
