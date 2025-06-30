Mint fac[N], ifac[N];
void init(int n) {
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * i;
	ifac[n] = 1 / fac[n];
	REV(i, n, 1) ifac[i-1] = ifac[i] * i;
}
Mint binom(int x, int y) {
	if (y > x || y < 0) return 0;
	return fac[x] * ifac[y] * ifac[x-y];
}
