struct Info { };
Info operator+ (const Info &a, const Info &b) {}
Info info[N<<2], init[N];
inline void PushUp(int x) { info[x] = info[x<<1] + info[x<<1|1]; }
inline void Build(int x, int l, int r) {
	if (l >= r) return info[x] = init[l], void ();
	int mid = l + (r - l) / 2;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	PushUp(x);
}
inline void Modify(int x, int l, int r, int pos, const Info &val) {
	if (l == pos && pos == r) return info[x] = val, void ();
	int mid = l + (r - l) / 2;
	if (pos <= mid) Modify(x<<1, l, mid, pos, val);
	if (pos > mid) Modify(x<<1|1, mid+1, r, pos, val);
	PushUp(x);
}
inline Info Query(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) return info[x];
	int mid = l + (r - l) / 2;
	if (R <= mid) return Query(x<<1, l, mid, L, R);
	if (mid < L) return Query(x<<1|1, mid+1, r, L, R);
	return Query(x<<1, l, mid, L, R) + Query(x<<1|1, mid+1, r, L, R);
}
