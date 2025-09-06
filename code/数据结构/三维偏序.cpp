struct BIT {
	int n; vector<int> t;
	BIT (int siz) : n(siz), t(siz+1, 0) {}
	void insert(int p, int v) {
		for (; p <= n; p += p&-p) t[p] += v;
	}
	int query(int p) {
		int ans = 0;
		for (; p; p &= p-1) ans += t[p];
		return ans;
	}
};
vector<int> solve(vector<array<int, 5>> a) { // x, y, z, qid, weight
	int n = ssize(a);
	REP(j, 0, 2) { // 离散化
		vector<int> c; c.reserve(n);
		REP(i, 0, n-1) c.push_back(a[i][j]);
		ranges::sort(c);
		c.erase(unique(c.begin(), c.end()), c.end());
		REP(i, 0, n-1) a[i][j] = lower_bound(c.begin(), c.end(), a[i][j]) - c.begin() + 1;
	} // 离散化
	REP(i, 0, n-1) a[i][3] = -a[i][3];
	ranges::sort(a, {}, [&] (auto i) { return array<int, 2> {i[0], i[3]}; });
	BIT t(n); vector<int> ans(n + 1); auto tmp = a;
	auto f = [&] (auto &&self, int l, int r) -> void {
		if (l >= r) return;
		int mid = l + (r - l) / 2;
		self(self, l, mid), self(self, mid+1, r);
		int i = l, j = mid+1, p = l;
		while (i <= mid || j <= r) {
			if (j > r || i <= mid && tie(a[i][1], a[i][3]) <= tie(a[j][1], a[j][3])) {
				if (!a[i][3]) t.insert(a[i][2], a[i][4]);
				tmp[p++] = a[i++];
			} else {
				if (a[j][3]) ans[-a[j][3]] += t.query(a[j][2] - 1);
				tmp[p++] = a[j++];
			}
		}
		REP(i, l, mid) if (!a[i][3]) t.insert(a[i][2], -a[i][4]);
		REP(i, l, r) a[i] = tmp[i];
	};
	return f(f, 0, n-1), ans;
}
