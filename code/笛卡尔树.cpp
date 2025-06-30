int lc[N], rc[N], s[N], n, p;
void build () { // v: i ; w: a[i] ; root=rc[0]
	for (int i = 1;i <= n;++i) { // 大根堆则是 <
		while (p && (a[s[p]] > a[i])) p--;
		lc[i] = rc[s[p]], rc[s[p]] = i, s[++p] = i;
	}
}
