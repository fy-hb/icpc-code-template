int f[N][20];
void init(int n) {
	REP(i, 1, __lg(n)) REP(j, 1, n-(1<<i)+1)
		f[j][i] = gcd(f[j][i-1], f[j+(1<<(i-1))][i-1]);
}
int get(int l, int r) {
	int k = __lg(r-l+1);
	return gcd(f[l][k], f[r-(1<<k)+1][k]);
}
