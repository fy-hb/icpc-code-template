struct B {
	int n, part, cnt;
	vector<i64> sum, sump, tag;
	vector<int> bel, L, R;
	B(int siz)
		: n(siz), part(max<int>(2, sqrt(n))), cnt((n - 1) / part + 1),
		  bel(n + 1), sum(n + 1), L(cnt + 1), R(cnt + 1), sump(cnt + 1), tag(cnt + 1) {
		REP(i, 1, n) {
			bel[i] = (i - 1) / part + 1;
			if (i % part == 1) L[bel[i]] = i;
			if (i % part == 0) R[bel[i]] = i;
		}
		R[bel[n]] = n;
	}
	void bAdd(int p, int l, int r, i64 v) {
		REP(i, l, r) sum[i] += v * (i - l + 1);
		REP(i, r+1, R[p]) sum[i] += v * (r - l + 1);
	}
	void rangeAdd(int l, int r, i64 v) {
		if (bel[l] == bel[r]) {
			bAdd(bel[l], l, r, v);
		} else {
			bAdd(bel[l], l, R[bel[l]], v);
			bAdd(bel[r], L[bel[r]], r, v);
		}
		REP(i, bel[l] + 1, bel[r] - 1) tag[i] += v;
		REP(i, 1, cnt) sump[i] = sump[i-1] + sum[R[i]] + tag[i] * (R[i] - L[i] + 1);
	}
	i64 bSum(int p, int l, int r) {
		return sum[r] - (l != L[p] ? sum[l-1] : 0) + tag[p] * (r - l + 1);
	}
	i64 rangeSum(int l, int r) {
		i64 ans = 0;
		if (bel[l] == bel[r]) {
			ans += bSum(bel[l], l, r);
		} else {
			ans += bSum(bel[l], l, R[bel[l]]);
			ans += bSum(bel[r], L[bel[r]], r);
			ans += sump[bel[r] - 1] - sump[bel[l]];
		}
		return ans;
	}
};
