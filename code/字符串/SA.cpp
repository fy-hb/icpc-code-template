struct SA {
vector<int> sa, rk, h, f; int siz;
SA(auto &S, int n, int m) : sa(n+1), rk(n+1), h(n+1), f(20*(n+1)), siz(n+1) {
	// SA
	vector<int> tmp(2*n+1), id(2*n+1);
	auto Sort = [&] () {
		vector<int> cnt(m + 1);
		REP(i, 1, n) cnt[rk[i]] += 1;
		REP(i, 1, m) cnt[i] += cnt[i-1];
		REV(i, n, 1) sa[cnt[rk[id[i]]]--] = id[i];
	};
	REP(i, 1, n) rk[i] = S[i], id[i] = i;
	Sort();
	for (int k = 1; k <= n; k <<= 1) {
		int cur = 0;
		REP(i, n-k+1, n) id[++cur] = i;
		REP(i, 1, n) if (sa[i] > k) id[++cur] = sa[i] - k;
		Sort();
		REP(i, 1, n) tmp[i] = rk[i];
		int num = rk[sa[1]] = 1;
		REP(i, 2, n) {
			if (tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k])
				rk[sa[i]] = num;
			else rk[sa[i]] = ++num;
		}
		m = num;
	}
	// Height
	int k = 0;
	REP(i, 1, n) {
		if (rk[i] == 1) continue;
		int j = sa[rk[i]-1];
		if (k) k --;
		while (i+k <= n && j+k <= n && S[i+k] == S[j+k]) k ++;
		h[rk[i]] = k;
	}
	// RMQ
	REP(i, 1, n) f[i] = h[i];
	REP(i, 1, __lg(n)) REP(j, 1, n-(1<<i)+1)
		f[i*siz+j] = min(f[(i-1)*siz+j], f[(i-1)*siz+j+(1<<(i-1))]);
}
int rmq(int l, int r) {
	int k = __lg(r-l+1);
	return min(f[k*siz+l], f[k*siz+r-(1<<k)+1]);
}
int lcp(int l, int r) {
	if (min(l, r) <= 0 || max(l, r) >= siz) return 0;
	if (l == r) return siz - l;
	l = rk[l], r = rk[r];
	if (l > r) swap(l, r);
	return rmq(l + 1, r);
}
};
