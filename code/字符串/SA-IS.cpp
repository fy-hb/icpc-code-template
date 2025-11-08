vector<int> sais(const auto& a) { // a[i] >= 1
	int n = ssize(a), m = ranges::max(a);
	vector<int> sa(n), cnt(m + 1), cur(m + 1);
	vector<char> typ(n); // 0L 1S
	REP(i, 0, n-1) cnt[a[i]] += 1;
	REP(i, 1, m) cnt[i] += cnt[i-1];
	REV(i, n-2, 0) typ[i] = a[i]==a[i+1] ? typ[i+1] : (a[i]<a[i+1]);
	auto insort = [&] (vector<int> &lms) {
		sa.assign(n, -1);
		int siz = ssize(lms);
		auto addL = [&] (int i) { if (i>=0 && !typ[i]) sa[cur[a[i]]++] = i; };
		auto addS = [&] (int i) { if (i>=0 &&  typ[i]) sa[--cur[a[i]]] = i; };
		REP(i, 1, m) cur[i] = cnt[i];
		REV(i, siz-1, 0) addS(lms[i]);
		REP(i, 1, m) cur[i] = cnt[i-1];
		addL(n-1);
		REP(i, 0, n-1) addL(sa[i]-1);
		REP(i, 1, m) cur[i] = cnt[i];
		REV(i, n-1, 0) addS(sa[i]-1);
	};
	auto check = [&] (int i) -> int { return i==n || (!typ[i-1]&&typ[i]); };
	auto lmseq = [&] (int i, int j) -> int {
		do { if (a[i++] != a[j++]) return 0; }
		while (!check(i) && !check(j));
		return check(i) && check(j);
	};
	vector<int> lms;
	REP(i, 1, n-1) if (check(i)) lms.push_back(i);
	insort(lms);
	if (!ssize(lms)) return sa;
	vector<int> mp(n);
	int cc = 0, last = -1;
	for (auto v : sa) if (v && check(v)) {
		if (last == -1 || !lmseq(last, v)) cc ++;
		mp[v] = cc, last = v;
	}
	auto b = lms;
	for (auto &v : b) v = mp[v];
	b = sais(b);
	for (auto &v : b) v = lms[v];
	insort(b);
	return sa;
}
vector<int> getHeight(const vector<int> &sa, const auto &a) {
	int n = ssize(sa), k = 0;
	vector<int> rk(n), h(n);
	REP(i, 0, n-1) rk[sa[i]] = i;
	REP(i, 0, n-1) {
		if (!rk[i]) continue;
		if (k) k --;
		int j = sa[rk[i]-1];
		while (i + k < n && j + k < n && a[i+k] == a[j+k]) k ++;
		h[rk[i]] = k;
	}
	return h;
}
