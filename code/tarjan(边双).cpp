vector<int> bcc[N]; vector<array<int, 2>> adj[N];
int dfn[N], low[N], st[N], bel[N], top, cnt, tms;
void tarjan(int u, int in) {
	low[u] = dfn[u] = ++tms, st[++top] = u;
	for (auto [v, id] : adj[u]) {
		if (id == in) continue;
		if (!dfn[v]) tarjan(v, id), chmin(low[u], low[v]);
		else chmin(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int z; cnt ++;
		do z = st[top--], bcc[cnt].push_back(z), bel[z] = cnt;
		while (z != u);
	}
}
