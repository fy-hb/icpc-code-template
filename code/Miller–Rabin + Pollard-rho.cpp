i64 mul(i64 a, i64 b, i64 p) {
	i64 z = a * (db(1) / p) * b + 0.5L, res = a * b - z * p;
	return res + (res >> 63 & p);
}
i64 qpow(i64 x, i64 y, i64 p, i64 res = 1) {
	for (; y; y >>= 1, x = mul(x, x, p))
		if (y & 1) res = mul(res, x, p);
	return res;
}
int MR(i64 p) {
	if (p == 1) return 0;
	i64 d = __builtin_ctzll(p - 1), s = (p - 1) >> d;
	for (auto a : {2, 3, 5, 7, 11, 13, 82, 373}) {
		if (a % p == 0) continue;
		i64 y, x = qpow(a, s, p);
		for (int i = 0; i < d; ++i, x = y) {
			y = mul(x, x, p);
			if (y == 1 && x != 1 && x != p - 1)
				return 0;
		}
		if (x != 1) return 0;
	}
	return 1;
}
i64 PR(i64 p) { // p > 1 && not prime
	if (!(p & 1)) return 2;
	i64 x = 0, y = 0, pp = 1;
	auto f = [p](i64 o) { return mul(o, o, p) + 1; };
	for (int t = 30, z = 0; t % 64 || gcd(pp, p) == 1; t ++) {
		if (x == y) x = ++z, y = f(x);
		if (i64 q = mul(pp, x + p - y, p)) pp = q;
		x = f(x), y = f(f(y));
	}
	return gcd(pp, p);
}
vector<i64> getfac(i64 x) {
	if (x == 1) return {};
	vector<i64> ans;
	auto f = [&] (auto &&self, i64 x) -> void {
		if (MR(x)) return ans.push_back(x);
		auto y = PR(x);
		self(self, y); self(self, x / y);
	};
	return f(f, x), ans;
}
