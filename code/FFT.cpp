using cp = complex<db>;
// cp::real  cp::imag  std::conj  std::arg
const db PI = acos(-1.L);
int rev[N], lim; cp wn[N];
void init(int siz) {
	lim = 2 << __lg(siz - 1);
	for (static int i = 1; i < lim; i <<= 1)
		for (int j = 0; j < i; j ++)
			wn[i+j] = polar(1.L, db(j) / db(i) * PI);
	for (int i = 1; i < lim; i ++)
		rev[i] = rev[i>>1] >> 1 | (i & 1 ? lim >> 1 : 0);
}
void dft(cp* a) {
	for (int i = 0; i < lim; i ++)
		if (rev[i] < i) swap(a[rev[i]], a[i]);
	for (int i = 1; i < lim; i <<= 1)
		for (int j = 0; j < lim; j += 2*i)
			for (int k = 0; k < i; k ++) {
				cp x = a[k+j] - a[i+j+k] * w[i+k];
				cp y = a[k+j] + a[i+j+k] * w[i+k];
				a[i+j+k] = x, a[k+j] = y;
			}
}
void idft(cp* a) {
	dft(a); reverse(a+1, a+lim);
	for (int i = 0; i < lim; i ++) a[i] /= lim;
}
