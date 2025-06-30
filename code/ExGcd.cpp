// result : -b < x < b AND -a < y <= a when a,b != 0
array<i64, 3> exgcd(i64 a, i64 b) {
	if (!b) return {a, 1, 0};
	auto [d, x, y] = exgcd(b, a % b);
	return {d, y, x - y * (a / b)};
}
