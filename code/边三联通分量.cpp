int dfn[N], out[N], low[N], deg[N], path[N], fa[N], cnt, tms;
vector<array<int, 2>> adj[N]; vector<int> tcc[N];
int find(int x) { return (x==fa[x]) ? x : (fa[x] = find(fa[x])); };
void unin(int x, int y) { fa[find(x)] = find(y); }
void dfs(int u, int in) {
	dfn[u] = ++tms;
	for (auto [v, id] : adj[u]) {
		if (v == u || id == in) continue;
		if (!dfn[v]) {
			dfs(v, id);
			if (!path[v] && deg[v] <= 1) {
				deg[u] += deg[v], chmin(low[u], low[v]);
			} else {
				if (!deg[v]) v = path[v];
				if (chmin(low[u], low[v])) swap(v, path[u]);
				for (; v; v = path[v]) unin(u, v), deg[u] += deg[v];
			}
		} else {
			if (dfn[v] < dfn[u]) {
				deg[u] ++, chmin(low[u], dfn[v]);
			} else {
				deg[u] --; int x = path[u];
				for (; x && dfn[x] <= dfn[v] && dfn[v] <= out[x]; x = path[x])
					unin(u, x), deg[u] += deg[x];
				path[u] = x;
			}
		}
	}
	out[u] = tms;
}
void solve(int n, int m) {
	REP(i, 0, n) {
		dfn[i] = out[i] = deg[i] = path[i] = 0;
		low[i] = 1E9, fa[i] = i, tcc[i].clear();
	}
	tms = cnt = 0;
	REP(i, 1, n) if (!dfn[i]) dfs(i, 0);
	REP(i, 1, n) tcc[find(i)].push_back(i);
	REP(i, 1, n) if (tcc[i].size()) tcc[++cnt].swap(tcc[i]);
}
