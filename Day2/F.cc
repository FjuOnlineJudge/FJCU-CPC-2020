#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
#include <set>
using namespace std;

const int HMAX = 1000;
const int WMAX = 1000;

int H, W, K, SX, SY, EX, EY;
bool rock[HMAX][WMAX];
set<int> rows[HMAX], cols[WMAX];
int D[HMAX][WMAX];
deque<pair<int, int>> Q;

static inline void update(int x, int y, int d) {
  rows[x].erase(y);
  cols[y].erase(x);
  D[x][y] = d;
  Q.emplace_back(x, y);
}

int solve() {
  memset(D, 0xFF, sizeof(D));
  update(SX, SY, 0);
  while (D[EX][EY] < 0 && !Q.empty()) {
    auto x = Q.front().first, y = Q.front().second;
    Q.pop_front();
    auto nd = D[x][y] + 1;
    set<int>::iterator it;
    while (true) {
      it = rows[x].upper_bound(y);
      if (it == rows[x].end() || rock[x][*it] || *it - y > K) break;
      update(x, *it, nd);
    }
    while (true) {
      auto ti = it;
      if (ti == rows[x].begin() || rock[x][*--ti] || y - *ti > K) break;
      update(x, *ti, nd);
    }
    while (true) {
      it = cols[y].upper_bound(x);
      if (it == cols[y].end() || rock[*it][y] || *it - x > K) break;
      update(*it, y, nd);
    }
    while (true) {
      auto ti = it;
      if (ti == cols[y].begin() || rock[*--ti][y] || x - *ti > K) break;
      update(*ti, y, nd);
    }
  }
  return D[EX][EY];
}

int main() {
  scanf("%d%d%d", &H, &W, &K);
  for (int x = 0; x < H; x++) {
    scanf(" ");
    for (int y = 0; y < W; y++) {
      if (getchar() != '.') rock[x][y] = true;
      rows[x].insert(y);
      cols[y].insert(x);
    }
  }
  scanf("%d%d%d%d", &SX, &SY, &EX, &EY); SX--; SY--; EX--; EY--;
  printf("%d\n", solve());
  return 0;
}
