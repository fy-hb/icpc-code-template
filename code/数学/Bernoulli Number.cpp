Z po = 1, inv4 = Z(1) / 4;
REP(i, 0, m) { // m = n / 2
	F[i] = inv[2 * i] * po;
	G[i] = inv[2 * i + 1] * po;
	po *= inv4;
}
F = F * G.inv(m + 1);
vector<Z> B(n + 1);
B[1] = -Z(1) / 2;
REP(i, 0, m) B[2 * i] = F[i] * fac[2 * i];
