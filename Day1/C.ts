declare function print(x: any): void;
declare function readline(): string | null | undefined;
const split = (s: string) => s.split(/\s+/);
const make_array = <T>(n: number, x: T): T[] => new Array(n).fill(x);
const build_array = <T>(n: number, f: (i: number) => T): T[] => {
  const a = new Array(n);
  for (let i = 0; i < n; i++) a[i] = f(i);
  return a;
};

const [N, V] = split(readline()!).map(Number);
const A = split(readline()!).map(Number);
const X = make_array(N, 0);
const B: number[][] = [];
const dfs = (d: number, x: number) => {
  if (d === N - 1) {
    X[N - 1] = V ^ x;
    if (X[N - 1] <= A[N - 1]) B.push([...X]);
    return;
  }
  for (let i = 0; i <= A[d]; i++) {
    X[d] = i;
    dfs(d + 1, x ^ i);
  }
};
dfs(0, 0);
print(B.length);
for (const x of B) print(`${x.join('^')}=${V}`);
