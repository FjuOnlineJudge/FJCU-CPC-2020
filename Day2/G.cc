#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

enum class Type {
  HEAL,
  ATK,
  DEF,
  HIT
};

struct Skill {
  Type type;
  int value;
};

Skill skills[2][10];
int cache[12][11][11][6][6][6][6];
bool done[12][11][11][6][6][6][6];

int negamax(int r, int hp0, int hp1, int atk0, int atk1, int def0, int def1) {
  if (hp0 <= 0) return r - 100;
  if (r == 12) return 0;
  auto &d = done[r][hp0][hp1][atk0][atk1][def0][def1];
  auto &res = cache[r][hp0][hp1][atk0][atk1][def0][def1];
  if (!d) {
    res = -1000;
    auto i = r & 1;
    for (int j = 0; j < 5 + r / 2; j++) {
      int t;
      switch(skills[i][j].type) {
        case Type::HEAL:
          t = -negamax(r + 1,
              hp1, min(10, hp0 + skills[i][j].value), atk1, atk0, def1, def0);
          break;
        case Type::ATK:
          t = -negamax(r + 1,
              hp1, hp0, atk1, max(atk0, skills[i][j].value), def1, def0);
          break;
        case Type::DEF:
          t = -negamax(r + 1,
              hp1, hp0, atk1, atk0, def1, max(def0, skills[i][j].value));
          break;
        case Type::HIT:
          t = -negamax(r + 1,
              hp1 - max(0, atk0 - def1), hp0, atk1, atk0, def1, def0);
      }
      res = max(res, t);
    }
    d = true;
  }
  return res;
}

void input() {
  char buf[10];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      scanf("%s", buf);
      if (buf[1] == 'I') { // HIT!
        skills[i][j].type = Type::HIT;
      } else {
        scanf("%d", &skills[i][j].value);
        if (buf[0] == 'H') { // Heal
          skills[i][j].type = Type::HEAL;
        } else if (buf[0] == 'A') { // Atk
          skills[i][j].type = Type::ATK;
        } else { // Def
          skills[i][j].type = Type::DEF;
        }
      }
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    input();
    memset(done, 0, sizeof(done));
    auto s = negamax(0, 10, 10, 0, 0, 0, 0);
    printf("Case #%d: %s %d\n", t, (s > 0 ? "win" : "lose"), 100 - abs(s));
  }
  return 0;
}
