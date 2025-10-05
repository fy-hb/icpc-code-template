int f[20][N];
void init(int n) {
	REP(i, 1, __lg(n)) REP(j, 1, n-(1<<i)+1)
		f[i][j] = gcd(f[i-1][j], f[i-1][j+(1<<(i-1))]);
}
int get(int l, int r) {
	int k = __lg(r-l+1);
	return gcd(f[k][l], f[k][r-(1<<k)+1]);
}
