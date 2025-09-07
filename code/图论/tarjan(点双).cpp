int dfn[N], low[N], st[N], bel[N], top, tms, cnt;
vector<int> adj[N], bcc[N]; // bel>1 为割点
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++tms, st[++top] = u; int ch = 0;
	for (auto v : adj[u]) {
		if (!dfn[v]) {
			tarjan(v, u), chmin(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				int z; cnt ++, ch ++;
				do z = st[top--], bel[z] ++, bcc[cnt].push_back(z);
				while (z != v);
				bcc[cnt].push_back(u), bel[u] ++;
			}
		}
		else chmin(low[u], dfn[v]);
	}
	if (!fa && !ch) bcc[++cnt] = {u};
}
