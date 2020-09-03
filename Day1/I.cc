#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

const int NMAX = 200000;

struct state {
  int dep;
  ll sum;
  state(int d, ll s) : dep(d), sum(s) { }
  bool operator<(const state &that) const { return sum > that.sum; }
};

int N, K, P[NMAX];
priority_queue<state> H;

int main() {
  scanf("%d%d", &N, &K);
  for (int i = 0; i < N; i++) scanf("%d", P + i);
  sort(P, P + N);
  H.emplace(0, P[0]);
  for (; ; ) {
    auto u = H.top();
    if (--K == 0) { printf("%lld\n", u.sum); break; }
    H.pop();
    if (u.dep + 1 == N) continue;
    H.emplace(u.dep + 1, u.sum + P[u.dep + 1]);
    H.emplace(u.dep + 1, u.sum + P[u.dep + 1] - P[u.dep]);
  }
  return 0;
}
