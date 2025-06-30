array<int, 2> res2(int n, int p) {
	if (!n) return {0, 0};
	if (qpow(n, p / 2, p) != 1) return {-1, -1};
	int t, ii; static mt19937_64 rnd(114514);
	do t = rnd() % p, ii = ((u64) t * t + p - n) % p;
	while (qpow(ii, p / 2, p) != p - 1);
	array<int, 2> ans = {1, 0}, x = {t, 1};
	auto mul = [&] (array<int,2> x, array<int,2> y)->array<int,2> {
		return {int(((u64) x[0] * y[0] + (u64) x[1] * y[1] % p * ii)%p),
				int(((u64) x[0] * y[1] + (u64) x[1] * y[0]) % p)}; };
	for (int y = p / 2 + 1; y; y >>= 1, x = mul(x, x))
		if (y & 1) ans = mul(ans, x);
	return {min(ans[0], p - ans[0]), max(ans[0], p - ans[0])};
}
