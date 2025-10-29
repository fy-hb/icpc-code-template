int dep[N], lb[N], fa[N];
void dfs(int u, int P) {
	dep[u] = dep[P] + 1, fa[u] = P;
	int X = lb[P], Y = lb[X];
	lb[u] = 2*dep[X]==dep[P]+dep[Y] ? Y : P;
	for (auto i : adj[u]) if (i != P) dfs(i, u);
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
