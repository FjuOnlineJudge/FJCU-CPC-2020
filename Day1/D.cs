using System;

class Program {
  static string[] split(string s) {
    char[] seps = { '\t', '\n', '\r', ' ' };
    return s.Split(seps, StringSplitOptions.RemoveEmptyEntries);
  }
  static T2[] map<T1, T2>(Func<T1, T2> f, T1[] a) {
    var n = a.Length;
    var b = new T2[n];
    for (int i = 0; i < n; i++) b[i] = f(a[i]);
    return b;
  }

  const int DMAX = 100000;
  static void Main() {
    Console.ReadLine();
    var d = map((s) => int.Parse(s), split(Console.ReadLine()));
    var n = d.Length;
    int a = int.MaxValue;
    var v = new int[DMAX * 2 * n + 1];
    Action<int, int, int> dfs = null;
    dfs = (dep, now, cnt) => {
      if (++v[now] == 1) cnt++;
      if (cnt < a) {
        if (dep == n) {
          a = cnt;
        } else {
          dfs(dep + 1, now + d[dep], cnt);
          dfs(dep + 1, now - d[dep], cnt);
        }
      }
      v[now]--;
    };
    dfs(0, DMAX * n, 0);
    Console.WriteLine(a);
  }
}
