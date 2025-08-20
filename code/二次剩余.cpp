constexpr u64 qpow(u64 x, u64 y, u32 mod) {
	u64 ans = 1;
	for (; y; y >>= 1, x *= x, x %= mod)
		if (y & 1) ans *= x, ans %= mod;
	return ans;
}
constexpr pair<int, int> res2(int n, int p) {
	if (!n) return {0, 0};
	if (qpow(n, p / 2, p) != 1) return {-1, -1};
	i64 t, I; static mt19937_64 rnd(233);
	do t = rnd() % p, I = (t * t + p - n) % p;
	while (qpow(I, p / 2, p) != p - 1);
	array<i64, 2> ans {1, 0}, x {t, 1};
	auto mul = [&] (array<i64,2> x, array<i64,2> y)->array<i64,2> {
		return {(x[0] * y[0] + x[1] * y[1] % p * I) % p,
				(x[0] * y[1] + x[1] * y[0]) % p}; };
	for (int y = p / 2 + 1; y; y >>= 1, x = mul(x, x))
		if (y & 1) ans = mul(ans, x);
	return minmax<int>(ans[0], p - ans[0]);
}
