i64 ceilDiv(i64 n, i64 m) { // m > 0
	return n >= 0 ? (n + m - 1) / m : n / m;
}
i64 floorDiv(i64 n, i64 m) { // m > 0
	return n >= 0 ? n / m : (n - m + 1) / m;
}
