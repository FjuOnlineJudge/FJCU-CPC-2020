#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> PII;

const int NMAX = 500;
const int MMAX = 500;
const int AMAX = 18;

int N, M, A; PII E[MMAX]; bool picked[NMAX];
int boz[NMAX], siz[NMAX];
vector<int> plst, vs, es, vset[NMAX], eset[NMAX];

void dfs(int dep, int now) {
  if (now >= A) return;
  if (dep == es.size()) {
    A = now;
    plst.clear();
    for (auto u : vs) if (picked[u]) plst.push_back(u);
    return;
  }
  if (picked[E[es[dep]].first] || picked[E[es[dep]].second]) {
    dfs(dep + 1, now);
  } else {
    picked[E[es[dep]].first] = true;
    dfs(dep + 1, now + 1);
    picked[E[es[dep]].first] = false;
    picked[E[es[dep]].second] = true;
    dfs(dep + 1, now + 1);
    picked[E[es[dep]].second] = false;
  }
}

void solve() {
  if (es.empty()) return;
  if (A == AMAX) throw 0;
  auto a = A;
  A = AMAX + 1;
  dfs(0, a);
  if (A > AMAX) throw 0;
  for (auto u : plst) picked[u] = true;
}

int Find(int x) {
  auto r = x;
  while (boz[r] != r) r = boz[r];
  for (; ; ) { auto t = boz[x]; if (t == r) break; boz[x] = r; x = t; }
  return r;
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
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) { boz[i] = i; siz[i] = 1; }
  for (int i = 0; i < M; i++) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--;
    E[i] = PII(a, b);
    Union(a, b);
  }
  for (int i = 0; i < N; i++) vset[Find(i)].push_back(i);
  for (int i = 0; i < M; i++) eset[Find(E[i].first)].push_back(i);
  try {
    for (int i = 0; i < N; i++) {
      if (boz[i] == i) {
        vs.swap(vset[i]);
        es.swap(eset[i]);
        solve();
      }
    }
  } catch (...) {
    puts("-1");
    return 0;
  }
  printf("%d\n", A);
  auto first = true;
  for (int i = 0; i < N; i++) {
    if (!picked[i]) continue;
    if (first) first = false; else putchar(' ');
    printf("%d", i + 1);
  }
  putchar('\n');
  return 0;
}
