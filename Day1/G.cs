using System;

class Program {
  static string[] split(string s) {
    char[] seps = { '\t', '\n', '\r', ' ' };
    return s.Split(seps, StringSplitOptions.RemoveEmptyEntries);
  }

  static void Main() {
    var input = split(Console.ReadLine());
    var N = int.Parse(input[0]);
    var K = long.Parse(input[1]);
    var F = new long[1 + N];
    F[0] = 1;
    for (int n = 1; n <= N; n++) F[n] = F[n - 1] * n;
    var D = new int[N];
    Action<int, int, int, int> dfs = null;
    dfs = (dep, ma, now, msk) => {
      if (dep == N) {
        if (--K == 0) {
          int mi = 0;
          for (int i = 1; i < N; i++) {
            D[i] += D[i - 1];
            mi = Math.Min(mi, D[i]);
          }
          mi--;
          for (int i = 0; i < N; i++) {
            if (i > 0) Console.Write(' ');
            Console.Write(D[i] - mi);
          }
          Console.WriteLine();
          Environment.Exit(0);
        }
        return;
      }
      var W = F[N - dep] * (N - ma);
      if (W < K) { K -= W; return; }
      for (var d = ma - now - N + 1; d < N - now; d++) {
        var x = now + d;
        if (x >= 0 && ((msk >> x) & 1) != 0) continue;
        D[dep] = d;
        if (x < 0) {
          dfs(dep + 1, ma - x, 0, (msk << -x) | 1);
        } else {
          dfs(dep + 1, Math.Max(ma, x), x, msk | (1 << x));
        }
      }
    };
    dfs(1, 0, 0, 1);
  }
}
