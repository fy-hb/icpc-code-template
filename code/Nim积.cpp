u64 ans[256][256];
u64 nimprod(u64 x, u64 y, int dep = 32) {
	if (!x || !y) return 0ull;
	if ((x | y) == 1ull) return 1ull;
	if (dep <= 4 && ans[x][y]) return ans[x][y];
	u64 a = x >> dep, c = y >> dep, b = x ^ a << dep, d = y ^ c << dep;
	u64 bd = nimprod(b, d, dep >> 1);
	u64 res = (nimprod(a ^ b, c ^ d, dep >> 1) ^ bd) << dep ^ 
			nimprod(1ull << (dep - 1), nimprod(a, c, dep >> 1), dep >> 1) ^ bd;
	if (dep <= 4) ans[x][y] = ans[y][x] = res;
	return res;
}
