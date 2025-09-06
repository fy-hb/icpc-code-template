const int N = 1e5+10;
bitset<N> vis;
vector<int> pr;
// Mobius函数, 欧拉函数
int mu[N], phi[N];
// 约数个数, 最小质因子数量
int d[N], num[N];
// 约数和, 最小质因子的p^0+p^1+...+p^k
int f[N], g[N];
static inline void Init(int n) {
	vis[1] = 1;
	mu[1] = 1;
	phi[1] = 1;
	d[1] = 1, num[1] = 0;
	g[1] = f[1] = 1;
	for (int i = 2; i <= n; i ++) {
		if (!vis[i]) {
			pr.push_back(i);
			mu[i] = -1;
			phi[i] = i-1;
			num[i] = 1, d[i] = 2;
			g[1] = f[1] = i+1;
		}
		for (auto j : pr) {
			if (i*j > n) break;
			vis[i*j] = 1;
			if (i%j == 0) {
				mu[i*j] = 0;
				phi[i*j] = phi[i]*j;
				num[i*j] = num[i]+1, d[i*j] = d[i] / (num[i]+1) * (num[i]+2);
				g[i*j] = g[i]*j+1, f[i*j] = f[i] / g[i] * g[i*j];
				break;
			}
			mu[i*j] = -mu[i];
			phi[i*j] = phi[i]*phi[j];
			num[i*j] = 1, d[i*j] = d[i] * 2;
			g[i*j] = j+1, f[i*j] = f[i]*f[j];
		}
	}
}
