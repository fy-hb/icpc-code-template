const int N = 500'000;
Info val[N], info[19][N];
void build(int n) {
	for (int h = 0, s = 1; s <= n; ++h, s <<= 1)
		for (int i = s; i <= n; i += s << 1) {
			info[h][i - 1] = val[i - 1];
			REV(j, i-1, i-s+1)
				info[h][j - 1] = val[j - 1] + info[h][j];
			if (i == n) break;
			info[h][i] = val[i];
			REP(j, i+1, min(i+s-1, n-1))
				info[h][j] = info[h][j - 1] + val[j];
		}
}
Info query(int l, int r) {
	if (l == r) return val[l];
	int h = __lg(l ^ r);
	return info[h][l] + info[h][r];
}
