using pt = array<i64, 2>;
pt operator+ (pt a, pt b) { return {a[0] + b[0], a[1] + b[1]}; }
pt operator- (pt a) { return {-a[0], -a[1]}; }
pt operator- (pt a, pt b) { return a + (-b); }
i64 operator* (pt a, pt b) { return a[0] * b[0] + a[1] * b[1]; }
i64 operator^ (pt a, pt b) { return a[0] * b[1] - a[1] * b[0]; }
db abs(pt a) { return __builtin_hypot(a[0], a[1]); }
i64 sq(pt a) { return a[0] * a[0] + a[1] * a[1]; }
int check(pt x, pt y, pt z) { return ((y - x) ^ (y - z)) < 0; }
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
