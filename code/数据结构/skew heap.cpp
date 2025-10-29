struct Node {
	i64 val; int fa, ls, rs, id;
} tr[N];
int root[N], cnt;
void apply(int u, ...) { }
void pushdown(int u) { }
int newnode(i64 val) { }
void join(int &x, int y) {
	if (!x || !y) return x |= y, void ();
	// pushdown(x), pushdown(y);
	if (tr[x].val > tr[y].val) swap(x, y);
	join(tr[x].rs, y);
	tr[tr[x].rs].fa = x;
	swap(tr[x].ls, tr[x].rs);
}
void decrease_key(int &h, int p, i64 v) {
	// pushdown(h), pushdown(p);
	int f = tr[p].fa, &s = f ? tr[f].ls == p ? tr[f].ls : tr[f].rs : h;
	s = tr[p].fa = 0, tr[p].val = v, join(h, p);
}
void erase(int &h, int x) {
	// pushdown(h), pushdown(x);
	decrease_key(h, x, LLONG_MIN);
	int l = tr[h].ls, r = tr[h].rs;
	join(h = l, r), tr[h].fa = 0;
}
