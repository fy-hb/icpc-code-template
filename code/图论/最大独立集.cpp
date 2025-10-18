u64 e[64], ee[64];
int Q[N], front, tail;
array<u64, 2> dfs(u64 S) {
	if (!S) return {1, 0};
	int maxd = 0, pos = -1;
	for (u64 i = S; i; i &= i-1) {
		int u = __builtin_ctzll(i);
		ee[u] = e[u] & S;
		int res = __builtin_popcountll(ee[u]);
		if (res > maxd) maxd = res, pos = u;
	}
	if (maxd <= 2) {
		u64 rem = S, sol = 0, cnt = 1;

		REP(_, 0, 1) for (u64 ss = rem; ss; ss &= ss-1) {
			int s = __builtin_ctzll(ss);
			if (!(rem >> s & 1)) continue;
			if (!_ && __builtin_popcountll(ee[s]) > 1) continue;

			front = tail = 0, Q[tail++] = s;

			u64 all = 1ull<<s;
			u64 select = all;
			u64 ban = 0ull;

			while (front < tail) {
				auto u = Q[front++];
				if (!(ban >> u & 1)) {
					select |= 1ull << u, ban |= ee[u];
				}
				for (u64 sss = (ee[u] | all) ^ all; sss; sss &= sss - 1) {
					int v = __builtin_ctzll(sss);
					Q[tail++] = v, all |= 1ull << v;
				}
			}
			int cc = __builtin_popcountll(all);
			rem ^= all, sol |= select;
			if (_) cnt *= cc & 1 ? cc : 2;
			else cnt *= cc & 1 ? 1 : cc / 2 + 1;
		}
		return {cnt, sol};
	}
	auto res1 = dfs(S ^ (1ull << pos) ^ ee[pos]);
	auto res0 = dfs(S ^ (1ull << pos));
	int cc1 = __builtin_popcountll(res1[1]) + 1;
	int cc0 = __builtin_popcountll(res0[1]);
	u64 sol = 0, cnt = 0;
	if (cc1 >= cc0) sol = res1[1] | 1ull << pos, cnt += res1[0];
	if (cc1 <= cc0) sol = res0[1], cnt += res0[0];

	return {cnt, sol};
}
