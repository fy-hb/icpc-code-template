const int N = 524288;
int f[19][N];
void init(int siz) {
	int x = __lg(siz) + 1, n = 1 << x;
	REP(j, 1, x-1) {
		int len = 1 << j;
		REP(i, 0, n-1) {
			if (len-1&i) f[j][i] = min(f[j][i-1], f[0][i]);
			else i += len, f[j][i] = f[0][i];
		}
		REV(i, n-1, 0) {
			if (len-1&i+1) f[j][i] = min(f[0][i], f[j][i+1]);
			else i -= len, f[j][i] = f[0][i];
		}
	}
}
int query(int l, int r) {
	if (l == r) return f[0][l];
	int x = __lg(l ^ r);
	return min(f[x][l], f[x][r]);
}
