void fmt(int* a) { // n = 1 << d
	REP(i, 0, d-1) REP(j, 0, n-1) if (1<<i&j)
		a[j] += a[j^(1<<i)];
}// ifmt: a[j] -= a[j^(1<<i)];
