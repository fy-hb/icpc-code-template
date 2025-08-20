void Add(i64 p, i64 v) { // 后缀加
	for (int x = p; x <= n; x += x&-x)
		ta[x] += v, tb[x] += p * v;
} // [l, r] ==> Add(l, v); Add(r+1, -v);
i64 Query(i64 p, i64 ans = 0) { // 前缀求和
	for (int x = p; x; x -= x&-x)
		ans += (p+1) * ta[x] - tb[x];
	return ans;
} // [l, r] ==> Query(r) - Query(l-1);
