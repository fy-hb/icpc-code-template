struct Tr { int v, w, ls, rs, siz; } tr[N];
inline void pushup(int u) {  }
inline void pushdown(int u) {  }
int merge(int x, int y) {
	if (!x || !y) return x ^ y;
	if (tr[x].w > tr[y].w)
		return pushdown(x), tr[x].rs = merge(tr[x].rs, y), pushup(x), x;
	return pushdown(y), tr[y].ls = merge(x,tr[y].ls), pushup(y), y;
}
void split(int u, int v, int &x, int &y) { // 按值: <= w | > w
	if (!u) return x = y = 0, void();
	pushdown(u);
	if (tr[u].v <= v) x = u, split(tr[u].rs, v, tr[u].rs, y);
	else y = u, split(tr[u].ls, v, x, tr[u].ls);
	pushup(u);
}
void split(int u, int siz, int &x, int &y) { // 按大小: siz | n-siz
	if (!u) return x = y = 0, void();
	pushdown(u);
	if (tr[tr[u].ls].siz + 1 > siz) y = u, split(tr[u].ls, siz, x, tr[u].ls);
	else x = u, split(tr[u].rs, siz - tr[tr[u].ls].siz - 1, tr[u].rs, y);
	pushup(u);
}
