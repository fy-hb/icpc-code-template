int son[N][2], fa[N], rev[N], val[N], sum[N];
bool get(int x, int p = 1) { return son[fa[x]][p] == x; }
void update(int x) {
	sum[x] = val[x] ^ sum[son[x][0]] ^ sum[son[x][1]];
}
int is_root(int x) { return !(get(x) || get(x, 0)); }
void rotate(int x) { // 注意 x y z !!!!!
	int y = fa[x], z = fa[y], b = get(x);
	if (!is_root(y)) son[z][get(y)] = x;
	son[y][b] = son[x][!b], son[x][!b] = y;
	fa[son[y][b]] = y, fa[y] = x, fa[x] = z; update(y);
}
void put(int x) {
	if (x) rev[x] ^= 1, swap(son[x][0], son[x][1]);
}
void down(int x) {
	if (rev[x]) put(son[x][0]), put(son[x][1]), rev[x] = 0;
}
void pushdown(int x) {
	if (!is_root(x)) pushdown(fa[x]);
	down(x);
}
void splay(int x) {
	for (pushdown(x); !is_root(x); rotate(x))
		if (!is_root(fa[x])) rotate(get(x)^get(fa[x]) ? x : fa[x]);
	update(x);
}
void access(int x) {
	for (int t = 0; x; son[x][1] = t, t = x, x = fa[x]) splay(x);
}
void mkroot(int x) {
	access(x), splay(x), put(x);
}
int find(int x) {
	access(x), splay(x);
	while (son[x][0]) x = son[x][0];
	return splay(x), x;
}
void split(int x, int y) {
	mkroot(x), access(y), splay(y);
}
void link(int x, int y) {
	mkroot(x);
	if(find(y)!=x) fa[x] = y;
}
void cut(int x, int y) {
	mkroot(x);
	if(find(y) == x && fa[y] == x && !son[y][0])
		fa[y] = son[x][1] = 0, update(x);
}
