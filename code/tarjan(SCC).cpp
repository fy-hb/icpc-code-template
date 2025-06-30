int dfn[N], low[N], bel[N], st[N], top, cnt, tms;
vector<int> adj[N], scc[N];
void tarjan(int u) {
	dfn[u] = low[u] = ++tms, st[++top] = u;
	for (auto v : adj[u]) {
		if (!dfn[v]) tarjan(v), chmin(low[u], low[v]);
		else if (!bel[v]) chmin(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int z; cnt ++;
		do z = st[top--], bel[z] = cnt, scc[cnt].push_back(z);
		while (z != u);
	}
}
