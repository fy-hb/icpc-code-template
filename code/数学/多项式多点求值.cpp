vector<Z> solve(const P &p, const vector<Z> &key) {
	int N = key.size();
	int L = 1;
	while (L < N) L *= 2;
	vector<P> div(L * 2);
	REP(i, N, L-1) div[L+i] = {1};
	REP(i, 0, N-1) div[L+i] = {-key[i], 1};
	REV(i, L-1, 1) div[i] = div[2*i] * div[2*i+1];
	vector<P> rem(2 * L);
	vector<bool> sol(2 * L);
	rem[1] = P::div(p, div[1]).second;
	vector<Z> res(N);
	REP(i, 1, 2*L-1) if (div[i].size() > 1) {
		if (sol[i/2]) { sol[i] = 1; continue; }
		if (i != 1) rem[i] = P::div(rem[i/2], div[i]).second;
		if (rem[i].size() <= 30) {
			int l = i, r = i+1;
			while (l < L) l *= 2, r *= 2;
			l -= L, r = min(r - L, N);
			auto &f = rem[i];
			REP(j, l, r-1) {
				Z c = 0;
				REV(k, ssize(f)-1, 0) (c *= key[j]) += f[k];
				res[j] = c;
			}
			sol[i] = 1;
		}
	}
	return res;
}
