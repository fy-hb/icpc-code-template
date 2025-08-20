const i64 INF = 2e16L;
struct Dinic {
struct Node { int to; i64 cap, flow; };
int n; vector<Node> e;
vector<int> cur, dis;
vector<vector<int>> adj;
Dinic(int siz) { n = siz; adj.assign(n+1, {}); }
void add(int u, int v, i64 w) {
	adj[u].push_back(e.size()); e.push_back({v, w, 0});
	adj[v].push_back(e.size()); e.push_back({u, 0, 0});
}
int bfs(int s, int t) {
	dis.assign(n+1, {}); cur.assign(n+1, {});
	queue<int> Q;
	for (Q.push(s), dis[s] = 1; Q.size(); ) {
		int u = Q.front(); Q.pop();
		for (auto i : adj[u]) {
			if (!dis[e[i].to] && e[i].cap-e[i].flow)
				dis[e[i].to] = dis[u] + 1, Q.push(e[i].to);
		}
	}
	return dis[t];
}
i64 dfs(int u, i64 flow, int t) {
	if (u == t || !flow) return flow;
	i64 sum = 0, res;
	for (int &id = cur[u]; id < ssize(adj[u]); id ++) {
		int i = adj[u][id];
		if (dis[e[i].to] == dis[u] + 1 && (res = dfs(e[i].to, min(flow, e[i].cap - e[i].flow), t))) {
			e[i].flow += res, e[i^1].flow -= res;
			sum += res, flow -= res;
			if (!flow) break;
		}
	}
	return sum;
}
i64 solve(int s, int t) {
	i64 ans = 0;
	for (; bfs(s, t); ) ans += dfs(s, INF, t);
	return ans;
}
};
