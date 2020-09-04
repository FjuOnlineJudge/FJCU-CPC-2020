declare function print(x: any): void;
declare function readline(): string | null | undefined;
const split = (s: string) => s.split(/\s+/);

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
const test = (x: number, y: number) => {
  if (Number.isSafeInteger(x) && 100 <= x && x < 1000 &&
      Number.isSafeInteger(y) && 100 <= y && y < 1000 &&
      diff(x, a) + diff(y, b) === 1) {
    print(`${x} ${y}`);
    return true;
  }
  return false;
};
test(a, c / a) || test(c / b, b);
