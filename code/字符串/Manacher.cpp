char a[N], b[N]; int p[N];
void solve(int n) { // 0-index
	REP(i, 0, n-1) b[2*i+1] = '.', b[2*i+2] = a[i];
	n = 2 * n + 3, b[0] = '#', b[n-2] = '.', b[n-1] = '$';
	int R = 0, id = 0;
	REP(i, 1, n-1) {
		p[i] = R > i ? min(p[2*id-i], R-i) : 1;
		while (b[i+p[i]] == b[i-p[i]]) p[i]++;
		if (i + p[i] > R) R = i + p[i], id = i;
	}
}
int check(int l, int r) { return p[l+r] >= r - l + 1; }
