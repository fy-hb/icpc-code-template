struct EK {
const i64 INF = 1e16L;
using pr = pair<i64, int>;
struct Node { int to; i64 vol, flow, cost; };
int n; vector<vector<int>> adj; vector<Node> e;
vector<int> from, vis; vector<i64> d, dis;
EK(int siz) {
	n = siz; adj.assign(n+1, {}); e = {{}, {}};
	from.assign(n+1, 0); vis.assign(n+1, 0);
	d.assign(n+1, 0); dis.assign(n+1, 0);
}
void add(int x, int y, i64 f, i64 c) {
	adj[x].push_back(e.size()); e.push_back({y, f, 0, c});
	adj[y].push_back(e.size()); e.push_back({x, 0, 0, -c});
}
int spfa(int s, int t) {
	queue<int> Q; d.assign(n+1, INF);
	for (d[s] = 0, vis[s] = 1, Q.push(s); Q.size(); ) {
		auto x = Q.front(); Q.pop(); vis[x] = 0;
		for (auto i : adj[x])
			if (e[i].vol - e[i].flow && d[e[i].to] > d[x] + e[i].cost) {
				d[e[i].to] = d[x] + e[i].cost; from[e[i].to] = i;
				if (!vis[e[i].to]) vis[e[i].to] = 1, Q.push(e[i].to);
			}
	}
	return d[t] < INF;
} 
int dij(int s, int t) {
	priority_queue<pr, vector<pr>, greater<pr>> Q;
	dis.swap(d); d.assign(n+1, INF);
	vis.assign(n+1, 0); from.assign(n+1, 0);
	for (Q.emplace(d[s] = 0, s); Q.size(); ) {
		auto x = Q.top().second; Q.pop();
		if (vis[x]) continue; vis[x] = 1;
		for (auto i : adj[x]) {
			const i64 v = e[i].cost + dis[x] - dis[e[i].to];
			if (e[i].vol - e[i].flow && d[e[i].to] > d[x] + v)
				from[e[i].to] = i, Q.emplace(d[e[i].to] = d[x]+v, e[i].to);
		}
	}
	for (int i = 0; i <= n; i ++) d[i] += dis[i]; return d[t] < INF;
}
array<i64, 2> solve(int s, int t) {
	spfa(s, t); i64 F = 0, C = 0, fl;
	for (; fl = INF, dij(s, t); ) {
		for (int i = from[t]; i; i = from[e[i^1].to])
			fl = min<i64> (e[i].vol - e[i].flow, fl);
		for (int i = from[t]; i; i = from[e[i^1].to])
			e[i].flow += fl, e[i^1].flow -= fl;
		F += fl, C += fl * d[t];
	}
	return {F, C};
}
};
