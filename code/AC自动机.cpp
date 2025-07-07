void init() {
	queue<int> Q;
	REP(i, 0, 25) if (tr[0][i]) Q.push(tr[0][i]);
	while (Q.size()) {
		int x = Q.front(); Q.pop();
		ch[fail[x]].push_back(x);
		REP(i, 0, 25) {
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				Q.push(tr[x][i]);
			} else tr[x][i] = tr[fail[x]][i];
		}
	}
}
