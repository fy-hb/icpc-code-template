int dfn[N], low[N], st[N], cut[N], top, tms, cnt;
vector<int> adj[N], bcc[N];
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++tms, st[++top] = u; int ch = 0;
	for (auto v : adj[u]) {
		if (!dfn[v]) {
			tarjan(v, u), chmin(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				if (++ch > 1 && fa) cut[u] = 1;
				int z; cnt ++;
				do z = st[top--], bcc[cnt].push_back(z);
				while (z != v);
				bcc[cnt].push_back(u);
			}
		}
		else chmin(low[u], dfn[v]);
	}
	if (!fa && !ch) bcc[++cnt] = {u}; // 特判独立点
}
