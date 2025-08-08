auto dfs = [&] (this auto &&self, int u) -> void {
	while (ssize(adj[u])) {
		auto [v, ind] = adj[u].back();
		adj[u].pop_back();
		if (vis[ind]) continue;
		vis[ind] = 1;
		self(v);
	}
	ans.push_back(u);
};
