// n = 1 << d;
// in: a/b[__builtin_popcount(i)][i];
REP(i, 0, d) fmt(a[i]), fmt(b[i]);
REP(i, 0, n-1) REP(j, 0, d) REP(k, 0, d-j)
	c[j+k][i] += 1ll * a[j][i] * b[k][i];
REP(i, 0, d) ifmt(c[i]);
// out: c[__builtin_popcount(i)][i]
