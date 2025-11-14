template <typename T>
constexpr T qpow(T x, u64 y, u32 mod) {
	T ans = 1;
	for (; y; y >>= 1, x = u64(x) * x % mod)
		if (y & 1) ans = u64(ans) * x % mod;
	return ans;
}
#define S (*this)
template <u32 mod, u32 root>
struct Poly : vector<Mint<mod>> {
	using Z = Mint<mod>;
	using vector<Z>::vector;
	static u32 lim, invlim, siz, rev[1<<20], wn[1<<20];
	static u64 tmp[1<<20];
	static constexpr void init(int n) {
		lim = n > 1 ? (2 << __lg(n - 1)) : 1;
		invlim = mod - (mod - 1) / lim;
		REP(i, 1, lim-1) rev[i] = rev[i>>1] >> 1 | (i&1 ? lim>>1 : 0);
		for (siz = max(siz, 1u); siz < lim; siz <<= 1) {
			Z w = Z(root).pow(mod / siz / 2), cur = 1;
			REP(j, 0, siz-1) wn[siz+j] = cur.val, cur *= w;
		}
	}
	constexpr void dft() {
		S.resize(lim);
		REP(i, 0, lim-1) tmp[i] = S[rev[i]].val;
		for (int i = 1; i < lim; i <<= 1) {
			for (int k = i & (1<<19); k--; )
				if (tmp[k] >= mod * 9ull) tmp[k] -= mod * 9ull;
			for (int j = 0; j < lim; j += 2 * i)
				for (int k = 0; k < i; k ++) {
					u64 x = tmp[i+j+k] * wn[i+k] % mod;
					tmp[i+j+k] = tmp[k+j] + mod - x; tmp[k+j] += x;
				}
		}
		REP(i, 0, lim-1) S[i] = tmp[i];
	}
	constexpr void idft() {
		dft(), ::reverse(S.begin()+1, S.end());
		for (auto &i : S) i *= invlim;
	}
	constexpr friend Poly operator* (Poly a, Poly b) {
		if (!a.size() || !b.size()) return {};
		assert(a.size() && b.size());
		int l = a.size() + b.size() - 1;
		if (min(ssize(a), ssize(b)) <= 32) {
			Poly c(l);
			REP(i, 0, ssize(a)-1)
				REP(j, 0, ssize(b)-1)
					c[i + j] += a[i] * b[j];
			return c;
		}
		init(l), a.dft(), b.dft();
		REP(i, 0, lim-1) a[i] *= b[i];
		return a.idft(), a.trunc(l);
	}
	constexpr friend Poly& operator*= (Poly &a, Z x) {
		for (auto &i : a) i *= x; return a;
	}
	constexpr friend Poly operator* (Poly a, Z x) {
		auto b = a; return b *= x, b;
	}
	constexpr friend Poly operator- (const Poly &a) {
		auto b = a;
		for (auto &i : b) i = -i;
		return b;
	}
	constexpr friend Poly& operator+= (Poly &a, const Poly &b) {
		if (ssize(b) > ssize(a)) a.resize(ssize(b));
		REP(i, 0, ssize(b)-1) a[i] += b[i];
		return a;
	}
	constexpr friend Poly& operator-= (Poly &a, const Poly &b) {
		return a += (-b);
	}
	constexpr friend Poly operator+ (const Poly &a, const Poly &b) {
		auto c = a; return c += b;
	}
	constexpr friend Poly operator- (const Poly &a, const Poly &b) {
		return a + (-b);
	}
	constexpr Poly rsh(int k) const {
		Poly res(max<int>(ssize(S) + k, 0), 0);
		REP(i, max(0, -k), ssize(S) - 1) res[i + k] = S[i];
		return res;
	}
	constexpr Poly trunc(int siz) const {
		if (siz <= S.size()) return Poly(S.begin(), S.begin() + siz);
		Poly t = S; t.resize(siz); return t;
	}
	constexpr Poly reverse() const {
		return Poly(S.rbegin(), S.rend());
	}
	constexpr Poly deriv() const {
		Poly res(max<int>(1, ssize(S) - 1));
		REP(i, 1, ssize(S)-1) res[i-1] = S[i] * i;
		return res;
	}
	constexpr Poly integr() const {
		Poly res(ssize(S) + 1);
		REP(i, 0, ssize(S)-1) res[i+1] = S[i] / (i+1);
		return res;
	}
	constexpr void invext(Poly &f) const {
		int d = ssize(f);
		auto t1 = trunc(2 * d);
		auto t2 = f.trunc(2 * d);
		init(2 * d);
		t1.dft(); t2.dft();
		REP(i, 0, lim-1) t1[i] *= t2[i];
		t1.idft();
		REP(i, 0, d-1) t1[i] = 0;
		t1.dft();
		REP(i, 0, lim-1) t1[i] *= t2[i];
		t1.idft();
		REP(i, 0, d-1) t1[i] = 0;
		f.resize(2 * d);
		REP(i, 0, lim-1) f[i] -= t1[i];
	}
	constexpr Poly inv(int n) const { // inv(a) (mod x^n)
		Poly x = {1 / S[0]};
		for (int t = 1; t < n; t <<= 1) {
			invext(x);
		}
		return x.trunc(n);
	}
	// constexpr Poly inv(int n) const { // inv(a) (mod x^n)
	// 	Poly x = {1 / S[0]};
	// 	for (int t = 2; t < 2*n; t <<= 1) {
	// 		x = (x * (Poly {2} - S.trunc(t) * x)).trunc(t);
	// 	}
	// 	return x.trunc(n);
	// }
	static constexpr pair<Poly, Poly> div(Poly f, Poly g) {
		// while (a.size() && a.back().val == 0) a.pop_back();
		int n = ssize(f), m = ssize(g);
		if (m == 0) return {};
		if (n < m) return {{}, f};
		auto q = (g.reverse().inv(n-m+1) * f.reverse()).trunc(n-m+1).reverse();
		return {q, (f - g * q).trunc(m - 1)};
	}
	constexpr Poly log(int n) const {
		return (S.deriv() * S.inv(n)).integr().trunc(n);
	}
	constexpr Poly exp(int n) const {
		Poly x = {1};
		for (int t = 2; t < 2 * n; t <<= 1) {
			x = (x * (Poly{1} - x.log(t) + S.trunc(t))).trunc(t);
		}
		return x.trunc(n);
	}
	constexpr Poly pow(u64 k, int n) const { // a^k (mod x^n)
		if (!k) return (Poly {1}).trunc(n);
		int i = 0;
		while (i < ssize(S) && S[i].val == 0) i ++;
		if (i == ssize(S) || i && k >= n || k * i >= n) return Poly(n);
		Z v = S[i];
		auto f = S.rsh(-i) * (1 / v);
		return (f.log(n - i * k) * Z(k)).exp(n - i * k).rsh(i * k) * v.pow(k);
	}
	Poly sqrt(int n) const {
		int i = 0;
		while (i < ssize(S) && S[i].val == 0) i ++;
		if (i == n) return Poly(n);
		if (i & 1) return {};
		auto a = S.rsh(-i);
		auto res = res2(a[0].val, mod);
		if (res.first == -1) return {};
		Poly x {res.first};
		for (int t = 2; t < 2 * (n - i / 2); t <<= 1) {
			x = (x + (a.trunc(t) * x.inv(t)).trunc(t)) * (Z(1) / 2);
		}
		return x.trunc(n - i / 2).rsh(i / 2);
	}
};
#undef S
template <u32 mod, u32 g> u32 Poly<mod, g>::lim;
template <u32 mod, u32 g> u32 Poly<mod, g>::siz;
template <u32 mod, u32 g> u32 Poly<mod, g>::invlim;
template <u32 mod, u32 g> u32 Poly<mod, g>::wn[];
template <u32 mod, u32 g> u32 Poly<mod, g>::rev[];
template <u32 mod, u32 g> u64 Poly<mod, g>::tmp[];
using P = Poly<998244353, 3>;
/*
 104857601  3 | 2^22 5^2
 880803841 26 | 2^23 3 5 7
 950009857  7 | 2^21 3 151
 998244353  3 | 2^23 7 17
1004535809  3 | 2^21 479
1107296257 10 | 2^25 3 11
12348030977 5 | 2^29 23
110595407873 3 | 2^30 103
1009317314561 3 | 2^32 5 47
10479720202241 3 | 2^35 5 61
106652627894273 3 | 2^40 97
1231453023109121 3 | 2^45 5 7
12947848928690177 3 | 2^49 23
112589990684262401 3 | 2^52 5^2
1261007895663738881 6 | 2^55 5 7
*/
