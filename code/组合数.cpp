namespace comb {
vector<Z> fac = {1}, ifac = {1}; int n;
void init(int m) {
	if (m < n) return;
	fac.resize(m+1), ifac.resize(m+1);
	REP(i, n+1, m) fac[i] = fac[i-1] * i;
	ifac[m] = 1 / fac[m];
	REV(i, m, n+1) ifac[i-1] = ifac[i] * i;
	n = m;
}
Z binom(int x, int y) {
	if (x < y || y < 0) return 0;
	init(2 * max(x, x-y));
	return fac[x] * ifac[y] * ifac[x-y];
}
};
