declare function print(x: any): void;
declare function readline(): string | null | undefined;
const split = (s: string) => s.split(/\s+/);
const make_array = <T>(n: number, x: T): T[] => new Array(n).fill(x);
const build_array = <T>(n: number, f: (i: number) => T): T[] => {
  const a = new Array(n);
  for (let i = 0; i < n; i++) a[i] = f(i);
  return a;
};

const [a, b, c] = split(readline()!).map(Number);
const diff = (x: number, y: number) => {
  let r = 0;
  for (let i = 0; i < 3; i++) {
    if (x % 10 !== y % 10) r++;
    x = Math.trunc(x / 10);
    y = Math.trunc(y / 10);
  }
  return r;
};
for (let aa = 100; aa < 1000; aa++) {
  if (c % aa > 0) continue;
  const bb = c / aa;
  if (bb < 100 || bb >= 1000) continue;
  if (diff(a, aa) + diff(b, bb) === 1) {
    print(`${aa} ${bb}`);
    break;
  }
}
