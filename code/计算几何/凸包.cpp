using P = array<i64, 2>;
P operator+ (P a, P b) { return {a[0] + b[0], a[1] + b[1]}; }
P operator- (P a) { return {-a[0], -a[1]}; }
P operator- (P a, P b) { return a + (-b); }
__int128 operator* (P a, P b) { return __int128(a[0]) * b[0] + __int128(a[1]) * b[1]; }
__int128 operator^ (P a, P b) { return __int128(a[0]) * b[1] - __int128(a[1]) * b[0]; }
db abs(P a) { return __builtin_hypotl(a[0], a[1]); }
__int128 sq(P a) { return a * a; }
int check(P x, P y, P z) { return ((y - x) ^ (y - z)) < 0; }
vector<int> work(const vector<P> &p) {
	if (!p.size()) return {};
	int n = p.size(), top = -1;
	vector<int> ord(n), st(n+1), vis(n);
	iota(ord.begin(), ord.end(), 0);
	ranges::sort(ord, {}, [&] (int i) { return p[i]; });
	int lim = 0; st[++top] = ord[0];
	REP(i, 0, 2*n-2) {
		int cur = ord[n - 1 - abs(n - 1 - i)];
		if (i == n) lim = top;
		if (vis[cur]) continue;
		while (top > lim && !check(p[st[top-1]], p[st[top]], p[cur]))
			vis[st[top]] = 0, top --;
		st[++top] = cur, vis[cur] = 1;
	}
	return st.resize(top + 1), st;
}
