P solve(vector<Z> key, vector<Z> val) {
	int N = key.size();
	int L = 1; while (L < N) L *= 2;
	vector<P> st(2 * L, P {1});
	REP(i, 0, N-1) st[L+i] = {1, -key[i]};
	REV(i, L-1, 1) st[i] = st[2*i] * st[2*i+1];
	auto tConv = [&] (const P &a, const P &b, int siz) -> P {
		int sizb = b.size();
		return (a.reverse() * b).reverse().rsh(-sizb + 1).trunc(siz);
	};
	vector<P> fp(2 * L);
	fp[1] = tConv(st[1].reverse().deriv(), st[1].inv(N), N);
	REP(i, 1, L-1) {
		fp[2*i] = tConv(fp[i], st[i*2+1], st[i*2].size() - 1);
		fp[2*i+1] = tConv(fp[i], st[i*2], st[i*2+1].size() - 1);
	}
	vector<Z> ax(N + 1);
	ax[0] = 1;
	REP(i, 0, N-1) ax[i+1] = ax[i] * fp[L+i][0];
	ax[N] = 1 / ax[N];
	REV(i, N-1, 0) {
		Z q = fp[L+i][0];
		fp[L+i][0] = ax[i] * ax[i+1] * val[i];
		ax[i] = ax[i+1] * q;
	}
	for(int i=L-1; i>=1; i--){
		fp[i] = fp[i*2] * st[i*2+1].reverse() + fp[i*2+1] * st[i*2].reverse();
	}
	return fp[1];
}
