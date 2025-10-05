int dfn[N], tms;
void dfs(int u, int ff) {
	dfn[u] = ++tms, f[0][tms] = {dfn[ff], ff};
	if (ff) adj[u].erase(find(adj[u].begin(), adj[u].end(), ff));
	for (auto i : adj[u]) dfs(i, u);
}
int lca(int u, int v) {
	if (u == v) return u;
	u = dfn[u], v = dfn[v];
	return get(min(u, v) + 1, max(u, v))[1];
}
