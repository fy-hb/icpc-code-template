constexpr array<Mint, 4> OR1  = {    1,     0,     1,      1};
constexpr array<Mint, 4> OR2  = {    1,     0,    -1,      1};
constexpr array<Mint, 4> AND1 = {    1,     1,     0,      1};
constexpr array<Mint, 4> AND2 = {    1,    -1,     0,      1};
constexpr array<Mint, 4> XOR1 = {    1,     1,     1,     -1};
constexpr array<Mint, 4> XOR2 = {1_M/2, 1_M/2, 1_M/2, -1_M/2};
constexpr void FWT(int n, Mint* a, array<Mint, 4> t) {
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k * 2) {
			for (int j = 0; j < k; j++) {
				auto tmp0 = a[i+j] * t[0] + a[i+j+k] * t[1];
				auto tmp1 = a[i+j] * t[2] + a[i+j+k] * t[3];
				a[i + j] = tmp0, a[i + j + k] = tmp1;
			}
		}
	}
}
