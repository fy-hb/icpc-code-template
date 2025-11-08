constexpr bool R(0), C(1);
vector<int> a;
struct Info {
	int u, v; array<array<int, 2>, 2> dp;
};
template <bool T> Info infoAdd(Info, Info);
/* [1] X.u/Y.u   [1] X.u
   / \           /
  /   \   ==>   /
[2]   [3]     [2]
X.v   Y.v     X.v             */
template <> Info infoAdd<R> (Info X, Info Y) {
	Info res {X.u, X.v};
	REP(x1, 0, 1) REP(x2, 0, 1) REP(x3, 0, 1)
		chmax(res.dp[x1][x2], X.dp[x1][x2] + Y.dp[x1][x3]);
	return res;
}
/* [1] X.u       X.u
   /             [1]
  /               |
[2] X.v/Y.u  ==>  |
  \              [3]
   \             Y.v
   [3] Y.v                    */
template <> Info infoAdd<C> (Info X, Info Y) {
	Info res {X.u, Y.v};
	REP(x1, 0, 1) REP(x2, 0, 1) REP(x3, 0, 1)
		chmax(res.dp[x1][x3], X.dp[x1][x2] + Y.dp[x2][x3]);
	return res;
}
struct Node {
	Info info;
	int fa, ch[2], siz;
	bool typ;
};
struct STT {
vector<Node> tr;
vector<vector<int>> adj;
vector<int> siz, idx, fa;
int cnt;
STT(int n) : tr(2*n+1), adj(n+1), siz(n+1), idx(n+1), fa(n+1) { }
void up(int u) {
	auto [c1, c2] = tr[u].ch;
	if (c1 && c2) {
		tr[u].info = (tr[u].typ == R ? infoAdd<R> : infoAdd<C>)
			(tr[c1].info, tr[c2].info);
	}
}
void dfs1(int u, int P) {
	if (P) adj[u].erase(find(adj[u].begin(), adj[u].end(), P));
	siz[u] = 1, fa[u] = P;
	for (auto &i : adj[u]) {
		tr[++cnt] = {.siz=1}, idx[i] = cnt; // !!!!!
		tr[cnt].info = {u, i, {{{{0, a[i]}}, {{0, -INF}}}}};
		dfs1(i, u);
		siz[u] += siz[i];
		if (siz[i] > siz[adj[u][0]]) swap(i, adj[u][0]);
	}
}
template<bool Ty>
int nodeAdd(int u, int v) {
	tr[++cnt] = {
		infoAdd<Ty>(tr[u].info, tr[v].info),
		0, {u, v}, tr[u].siz + tr[v].siz, Ty};
	tr[u].fa = tr[v].fa = cnt;
	return cnt;
}
template<bool Ty>
int merge(const vector<int> &vec, int l, int r) {
	if (l == r) return vec[l];
	int mid = r - 1, sum = 0, cur = 0;
	REP(i, l, r) sum += tr[vec[i]].siz;
	REP(i, l, r-1) if ((cur += tr[vec[i]].siz) * 2 >= sum) {
		mid = i; break;
	}
	return nodeAdd<Ty>(merge<Ty>(vec, l, mid), merge<Ty>(vec, mid+1, r));
}
int dfs2(int tt) {
	vector<int> ch;
	if (idx[tt]) ch.push_back(idx[tt]);
	for (int u = tt; ssize(adj[u]); u = adj[u][0]) {
		vector<int> son;
		for (auto i : adj[u]) {
			if (i != adj[u][0]) son.push_back(dfs2(i));
		}
		if (!ssize(son)) ch.push_back(idx[adj[u][0]]);
		else ch.push_back(nodeAdd<R>(idx[adj[u][0]],
			merge<R>(son, 0, ssize(son)-1)));
	}
	return merge<C>(ch, 0, ssize(ch)-1);
}
void add(int u, int v) {
	adj[u].push_back(v), adj[v].push_back(u);
}
void solve(int root) {
	dfs1(root, 0); dfs2(root);
}
void modify(int u, const Info &info) {
	tr[idx[u]].info = info;
	for (int i = idx[u]; i; i = tr[i].fa) up(i);
}
};
