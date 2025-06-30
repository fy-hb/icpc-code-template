using pt = array<i64, 2>;
pt operator+ (pt a, pt b) { return {a[0] + b[0], a[1] + b[1]}; }
pt operator- (pt a, pt b) { return {a[0] - b[0], a[1] - b[1]}; }
i64 operator* (pt a, pt b) { return a[0] * b[0] + a[1] * b[1]; }
i64 operator^ (pt a, pt b) { return a[0] * b[1] - a[1] * b[0]; }
pt operator- (pt a) { return {-a[0], -a[1]}; }
db abs(pt a) { return __builtin_hypot(a[0], a[1]); }
i64 sq(pt a) { return a[0] * a[0]+ a[1] * a[1]; }
int check(pt x, pt y, pt z) { return ((y - x) ^ (y - z)) < 0; }
vector<int> work(const vector<pt> &p) {
	if (!p.size()) return {};
	int n = p.size(), top = -1;
	vector<int> ind(n), st(n+1), vis(n);
	REP(i, 0, n-1) ind[i] = i;
	ranges::sort(ind, [&] (int i, int j) { return p[i] < p[j]; });
	st[++top] = ind[0];
	REP(i, 0, n-1) {
		while (top >= 1 && !check(p[st[top-1]], p[st[top]], p[ind[i]]))
			vis[st[top]] = 0, top --;
		st[++top] = ind[i]; vis[ind[i]] = 1;
	}
	int siz = top;
	REV(i, n-2, 0) {
		if (vis[ind[i]]) continue;
		while (top > siz && !check(p[st[top-1]], p[st[top]], p[ind[i]]))
			vis[st[top]] = 0, top --;
		st[++top] = ind[i]; vis[ind[i]] = 1;
	}
	return st.resize(top), st;
}
