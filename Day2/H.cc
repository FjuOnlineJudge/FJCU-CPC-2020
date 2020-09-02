#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;
typedef long long ll;

const int NMAX = 200000;

unordered_set<ll> S;

static inline bool exist(int a, int b) {
  if (a > b) swap(a, b);
  return S.find((ll)a * NMAX + b) == S.end();
}

int main() {
  int N, m;
  scanf("%d%d", &N, &m);
  while (m-- > 0) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--;
    if (a > b) swap(a, b);
    S.insert((ll)a * NMAX + b);
  }
  vector<int> remain, mylist, temp, ans;
  for (int i = 0; i < N; i++) remain.push_back(i);
  while (!remain.empty()) {
    mylist.push_back(remain.back());
    remain.pop_back();
    for (int i = 0; i < (int)mylist.size(); i++) {
      for (auto j : remain) {
        if (exist(mylist[i], j)) {
          mylist.push_back(j);
        } else {
          temp.push_back(j);
        }
      }
      remain.clear();
      remain.swap(temp);
    }
    ans.push_back(mylist.size());
    mylist.clear();
  }
  sort(ans.begin(), ans.end());
  printf("%d\n%d", (int)ans.size(), ans[0]);
  for (int i = 1; i < ans.size(); i++) printf(" %d", ans[i]);
  putchar('\n');
  return 0;
}
