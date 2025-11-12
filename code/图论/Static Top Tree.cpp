constexpr int INF = 1E9;
struct Info { array<array<int, 2>, 2> dp; };
/* [1] X.u/Y.u   [1] X.u
   / \    ==>    /
 [2] [3]       [2] X.v
X.v  Y.v                      */
Info Rake(Info X, Info Y) {
	Info res {};
	REP(x1, 0, 1) REP(x2, 0, 1) REP(x3, 0, 1)
		chmax(res.dp[x1][x2], X.dp[x1][x2] + Y.dp[x1][x3]);
	return res;
}
/* [1] X.u        X.u
   /              [1]
 [2] X.v/Y.u  ==>  |
   \              [3]
   [3] Y.v        Y.v         */
Info Compress(Info X, Info Y) {
	Info res {};
	REP(x1, 0, 1) REP(x2, 0, 1) REP(x3, 0, 1)
		chmax(res.dp[x1][x3], X.dp[x1][x2] + Y.dp[x2][x3]);
	return res;
}
struct Node { Info data; int fa, siz, ch[2]; char op; };
struct STT {
vector<Node> tr;
vector<vector<int>> adj;
vector<int> siz, idx, chidx;
int cnt;
STT(int n) : tr(2*n+1), adj(n+1), siz(n+1), idx(n+1), chidx(n+1), cnt(0) { }
inline Info getInfo(int v, int u) { // Cluster of {u as parent, v} !!!!!
	return {u, v, {{{{0, a[v]}}, {{0, -INF}}}}};
}
void pushup(int u) {
	tr[u].data = (tr[u].op=='R'?Rake:Compress)(tr[tr[u].ch[0]].data, tr[tr[u].ch[1]].data);
}
void dfs1(int u, int P) {
	if (P) adj[u].erase(find(adj[u].begin(), adj[u].end(), P));
	siz[u] = 1;
	for (auto &i : adj[u]) {
		dfs1(i, u);
		tr[++cnt] = {.data=getInfo(i, u), .siz=1, .op='-'};
		idx[i] = cnt, siz[u] += siz[i];
		if (siz[i] > siz[adj[u][0]]) swap(i, adj[u][0]);
	}
}
int merge(int u, int v, char op) {
	return tr[++cnt] = {.siz=tr[u].siz+tr[v].siz, .ch={u, v}, .op=op}
		, pushup(cnt), tr[u].fa = tr[v].fa = cnt;
}
int build(const vector<int> &vec, int l, int r, char op) {
	if (l == r) return vec[l];
	int mid = r - 1, sum = 0, cur = 0;
	REP(i, l, r) sum += tr[vec[i]].siz;
	REP(i, l, r-1) if ((cur += tr[vec[i]].siz)*2 >= sum)
		{ mid = i; break; }
	return merge(build(vec, l, mid, op), build(vec, mid+1, r, op), op);
}
int dfs2(int tt) {
	vector<int> ch;
	if (idx[tt]) ch.push_back(idx[tt]);
	for (int u = tt; ssize(adj[u]); u = adj[u][0]) {
		chidx[u] = idx[adj[u][0]];
		vector<int> son;
		for (auto i : adj[u]) if (i != adj[u][0]) son.push_back(dfs2(i));
		if (ssize(son)) chidx[u] = merge(chidx[u], build(son, 0, ssize(son)-1, 'R'), 'R');
		ch.push_back(chidx[u]);
	}
	return build(ch, 0, ssize(ch)-1, 'C');
}
void addEdge(int u, int v) {
	adj[u].push_back(v), adj[v].push_back(u);
}
void solve(int root) { dfs1(root, 0); dfs2(root); }
void modify(int u, const Info &info) {
	u = idx[u], tr[u].data = info;
	for (u = tr[u].fa; u; u = tr[u].fa) pushup(u);
}
Info queryC(int u) {
	assert(chidx[u]);
	u = chidx[u]; Info res = tr[u].data;
	for (; tr[u].fa && tr[tr[u].fa].op != 'R'; u = tr[u].fa)
		if (u == tr[tr[u].fa].ch[0]) res = Compress(res, tr[tr[tr[u].fa].ch[1]].data);
	return res;
}
Info queryF(int u) {
	assert(idx[u]);
	Info res = tr[idx[u]].data;
	if (ssize(adj[u])) res = Compress(res, queryC(u));
	return res;
}
};
