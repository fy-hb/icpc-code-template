array<i64, 2> exCRT(i64 a1, i64 p1, i64 a2, i64 p2) {
	auto [g, a, b] = exgcd(p1, p2);
	if ((a1 - a2) % g) return {-1, 0};
	i64 k = __int128((a2 - a1) % p2 + p2) * (a + p2) % p2;
	return {p1 / g * k + a1, p1 / g * p2};
}
