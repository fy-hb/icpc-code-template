int dep[N], lb[N], fa[N];
void dfs(int u, int ff) {
	dep[u] = dep[ff] + 1, fa[u] = ff;
	if (ff) adj[u].erase(find(adj[u].begin(), adj[u].end(), ff));
	int x = lb[ff], y = lb[x];
	lb[u] = 2*dep[x]==dep[ff]+dep[y] ? y : ff;
	for (auto i : adj[u]) dfs(i, u);
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) {
		if (dep[lb[u]] < dep[v]) u = fa[u];
		else u = lb[u];
	}
	while (u != v) {
		if (lb[u] == lb[v]) u = fa[u], v = fa[v];
		else u = lb[u], v = lb[v];
	}
	return u;
}
