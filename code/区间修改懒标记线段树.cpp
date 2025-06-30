struct Tag {
	void apply(const Tag &t) {}
	static Tag Id() {}
};
struct Info {
	void apply(const Tag &t) {}
};
Info operator+ (const Info &a, const Info &b) {}
Info info[N<<2], init[N]; Tag tag[N<<2];
inline void PushUp(int x) {
	info[x] = info[x<<1] + info[x<<1|1];
}
inline void Apply(int x, const Tag &val) {
	info[x].apply(val); tag[x].apply(val);
}
inline void PushDown(int x) {
	Apply(x<<1, tag[x]); Apply(x<<1|1, tag[x]); tag[x] = Tag::Id();
}
inline void Build(int x, int l, int r) {
	tag[x] = Tag::Id();
	if (l >= r) return info[x] = init[l], void ();
	int mid = l + (r - l) / 2; Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r); PushUp(x);
}
inline void Modify(int x, int l, int r, int pos, const Info &val) {
	if (l == pos && pos == r) return info[x] = val, void ();
	PushDown(x); int mid = l + (r - l) / 2;
	if (pos <= mid) Modify(x<<1, l, mid, pos, val);
	if (pos > mid) Modify(x<<1|1, mid+1, r, pos, val);
	PushUp(x);
}
inline void Add(int x, int l, int r, int L, int R, const Tag &val) {
	if (L <= l && r <= R) return Apply(x, val), void ();
	PushDown(x); int mid = l + (r - l) / 2;
	if (mid >= L) Add(x<<1, l, mid, L, R, val);
	if (R > mid) Add(x<<1|1, mid+1, r, L, R, val);
	PushUp(x);
}
inline Info Query(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) return info[x];
	PushDown(x); int mid = l + (r - l) / 2;
	if (R <= mid) return Query(x<<1, l, mid, L, R);
	if (mid < L) return Query(x<<1|1, mid+1, r, L, R);
	return Query(x<<1, l, mid, L, R) + Query(x<<1|1, mid+1, r, L, R);
}
