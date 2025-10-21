template <int k>
constexpr Z powsum(i64 x) {
	constexpr Z f[11][12] = {
		{0, 1},
		{0, 1, 1},
		{0, 1, 3, 2},
		{0, 0, 1, 2, 1},
		{0, -1, 0, 10, 15, 6},
		{0, 0, -1, 0, 5, 6, 2},
		{0, 1, 0, -7, 0, 21, 21, 6},
		{0, 0, 2, 0, -7, 0, 14, 12, 3},
		{0, -3, 0, 20, 0, -42, 0, 60, 45, 10},
		{0, 0, -3, 0, 10, 0, -14, 0, 15, 10, 2},
		{0, 5, 0, -33, 0, 66, 0, -66, 0, 55, 33, 6},
	};
	constexpr Z g[] = {1, 2, 6, 4, 30, 12, 42, 24, 90, 20, 66};
	constexpr Z inv = 1 / g[k];
	Z ans {}, p = 1;
	REP(i, 1, k+1) p *= x, ans += p * f[k][i] * inv;
	return ans;
}
constexpr Z calcfp(i64 p, int c) {
	return p ^ c;
}
constexpr Z coeff[] = {-1, 1};
constexpr Z patch(i64 val) {
	if (val >= 2) return 2;
	else return 0;
}

const int N = 1E5 + 10;
bitset<N> vis;
int pr[N], id1[N], id2[N];
i64 val[2*N];
Z g[2*N], G[2*N];
i64 n; int cnt, sqr, siz;

void init(i64 x) {
	n = x, sqr = sqrt(n);
	vis[1] = 1;
	REP(i, 2, sqr) {
		if (!vis[i]) pr[++siz] = i;
		REP(j, 1, siz) {
			if (i * pr[j] > sqr) break;
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	for (i64 l = 1, r, v; l <= n; l = r + 1) {
		r = n / (n / l), v = n / l;
		val[++cnt] = v;
		if (v <= sqr) id1[v] = cnt;
		else id2[n / v] = cnt;
	}
}
int getid(i64 x) { // !!
	return x <= sqr ? id1[x] : id2[n / x];
}
template<int ii>
void getG() {
	REP(i, 1, cnt) g[i] = powsum<ii>(val[i]) - 1;
	REP(j, 1, siz) {
		int p = pr[j], last = pr[j-1];
		Z po = Z(p).pow(ii);
		REP(i, 1, cnt) {
			if (p > val[i] / p) break;
			g[i] -= po * (g[getid(val[i] / p)] - g[getid(last)]);
		}
	}
	REP(i, 1, cnt) G[i] += g[i] * coeff[ii];
	if constexpr (ii > 0) getG<ii-1>();
}
Z S(i64 x, int y) {
	if (pr[y] >= x) return 0;
	Z res = G[getid(x)] - G[getid(pr[y])];
	REP(j, y+1, siz) {
		if (pr[j] > x / pr[j]) break;
		i64 cur = pr[j];
		REP(cc, 1, 100) {
			if (cur > x / pr[j]) break;
			res += calcfp(pr[j], cc) * S(x / cur, j) + calcfp(pr[j], cc+1);
			cur *= pr[j];
		}
	}
	return res;
}
Z solve(i64 x) {
	init(x);
	getG<ssize(coeff)-1> ();
	REP(i, 1, cnt) G[i] += patch(val[i]);
	return S(n, 0) + 1;
}
