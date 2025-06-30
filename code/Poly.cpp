constexpr int mod = 998'244'353;
constexpr int qpow(int x, int y, int m = mod, int ans = 1) {
	for (; y; y >>= 1, x = (u64) x * x % m)
		if (y & 1) ans = (u64) ans * x % m;
	return ans;
}
using P = vector<int>;
vector<int> rev, wn;
int lim, invlim;
void init(int n) {
	lim = max(2 << __lg(n - 1), 1);
	invlim = mod - (mod - 1) / lim;
	if (lim > wn.size()) wn.resize(lim);
	rev.resize(lim);
	for (static int i = 1; i < lim; i <<= 1) {
		int w = qpow(3, mod / i / 2), cur = 1;
		for (int j = 0; j < i; j ++)
			wn[i+j] = cur, cur = (u64) cur * w % mod;
	}
	REP(i, 1, lim-1) rev[i] = rev[i>>1] >> 1 | (i&1 ? lim>>1 : 0);
}
P trunc(const P &a, int siz) {
	if (siz <= a.size()) return P(a.begin(), a.begin() + siz);
	P res = a; res.resize(siz); return res;
}
P reverse(const P &v) { return P(v.rbegin(), v.rend()); }
P dft(const P &a) {
	static vector<u64> tmp;
	tmp.assign(lim, 0);
	REP(i, 0, a.size()-1) tmp[rev[i]] = a[i];
	for (int i = 1; i < lim; i <<= 1) {
		for (int k = i & (1 << 19); k--; )
			if (tmp[k] >= mod * 9ull) tmp[k] -= mod * 9ull;
		for (int j = 0; j < lim; j += 2 * i)
			for (int k = 0; k < i; k ++) {
				const u64 x = (u64) tmp[i+j+k] * wn[i+k] % mod;
				tmp[i+j+k] = tmp[k+j] + mod - x; tmp[k+j] += x;
			}
	}
	REP(i, 0, lim-1) tmp[i] %= mod;
	return P(tmp.begin(), tmp.end());
}
P idft(const P &a) {
	auto b = dft(a); reverse(b.begin()+1, b.end());
	for (auto &i : b) i = (u64) i * invlim % mod;
	return b;
}
P operator- (const P &a) {
	P c = a;
	for (auto &i : c) i = i ? mod - i : 0;
	return c;
}
P operator+ (const P &a, const P &b) {
	P c(max(a.size(), b.size()));
	REP(i, 0, a.size()-1) c[i] += a[i];
	REP(i, 0, b.size()-1) c[i] += b[i], c[i] >= mod && (c[i] -= mod);
	return c;
}
P operator- (const P &a, const P &b) {
	return a + (-b);
}
P operator* (const P &a, const P &b) {
	assert(a.size() && b.size());
	int l = a.size() + b.size() - 1;
	init(l);
	auto c = dft(a), d = dft(b);
	REP(i, 0, lim-1) c[i] = (u64) c[i] * d[i] % mod;
	auto res = idft(c);
	return trunc(res, l);
}
P operator* (const P &a, int b) {
	auto x = trunc(a, a.size());
	for (auto &i : x) i = (u64) i * b % mod;
	return x;
}
P inv(const P &a) { // inv(a) (mod x^n)
	int n = a.size();
	P x = {qpow(a[0], mod-2)};
	for (int t = 2; t < 2 * n; t <<= 1)
		x = trunc((P {2} - trunc(a, t) * x) * x, t);
	return trunc(x, n);
}
pair<P, P> div(const P &f, const P &g) { // f = g * q + r
	int n = f.size(), m = g.size();
	auto q = reverse(trunc(reverse(f) * inv(trunc(reverse(g), n-m+1)), n-m+1));
	auto r = trunc(f - g * q, m - 1);
	return {q, r};
}
P sqrt(const P &a) { // sqrt(a) (mod x^n);
	P b {res2(a[0], mod)[0]};
	if (b[0] < 0) return {};
	int n = a.size();
	for (int t = 2; t < 2 * n; t <<= 1)
		b = trunc((trunc(a, t) + b * b) * inv(trunc(b * 2, t)), t);
	return trunc(b, n);
}
P deriv(const P &a) {
	int n = a.size(); if (!n) return {}; P res(n - 1);
	REP(i, 0, n-2) res[i] = (u64) a[i + 1] * (i + 1) % mod;
	return res;
}
P integr(const P &a) {
	int n = a.size(); P res(n + 1);
	REP(i, 1, n) res[i] = (u64) a[i - 1] * qpow(i, mod-2, mod) % mod;
	return res;
}
P log(const P &a) {
	return trunc(integr(deriv(a) * inv(a)), a.size());
}
P exp(const P &a) {
	int n = a.size(); P b {1};
	for (int t = 2; t < 2 * n; t <<= 1)
		b = trunc(b * (P {1} - log(trunc(b, t)) + trunc(a, t)), t);
	return trunc(b, n);
}
