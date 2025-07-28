struct B {
	int n, part, cnt;
	vector<i64> sum0, sum1, d0;
	vector<int> bel, L, R;
	B(int siz)
		: n(siz), part(max<int>(2, sqrt(n))), cnt((n - 1) / part + 1),
		  bel(n + 1), d0(n + 1), L(cnt + 1), R(cnt + 1), sum0(cnt + 1), sum1(cnt + 1) {
		REP(i, 1, n) {
			bel[i] = (i - 1) / part + 1;
			if (i % part == 1) L[bel[i]] = i;
			if (i % part == 0) R[bel[i]] = i;
		}
		R[bel[n]] = n;
	}
	void sufAdd(int x, i64 v) {
		d0[x] += v, sum0[bel[x]] += v, sum1[bel[x]] += v * x;
	}
	void rangeAdd(int l, int r, i64 v) {
		sufAdd(l, v);
		if (r + 1 <= n) sufAdd(r + 1, -v);
	}
	i64 preSum(int x) {
		i64 sum = 0;
		REP(i, 1, bel[x] - 1) sum += sum0[i] * (x + 1) - sum1[i];
		REP(i, L[bel[x]], x) sum += d0[i] * (x - i + 1);
		return sum;
	}
	i64 rangeSum(int l, int r) { return preSum(r) - preSum(l - 1); }
};
