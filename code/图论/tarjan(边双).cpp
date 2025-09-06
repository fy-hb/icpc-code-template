vector<int> bcc[N], adj[N];
int dfn[N], low[N], st[N], bel[N], top, cnt, tms;
void tarjan(int u, int p) {
	low[u] = dfn[u] = ++tms, st[++top] = u;
	for (auto v : adj[u]) {
		if (v == p) { p = 0; continue; }
		if (!dfn[v]) tarjan(v, u), chmin(low[u], low[v]);
		else chmin(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int z; cnt ++;
		do z = st[top--], bel[z] = cnt, bcc[cnt].push_back(z);
		while (z != u);
	}
}
