// OR : {1,0,1,1} / {1,0,-1,1}
// AND: {1,1,0,1} / {1,-1,0,1}
// XOR: {1,1,1,-1}/ {1/2, 1/2, 1/2, -1/2}
constexpr void FWT(int n, Z* a, array<Z, 4> ty) {
	for (int k = 1; k < n; k <<= 1)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				auto tmp0 = a[i+j] * ty[0] + a[i+j+k] * ty[1];
				auto tmp1 = a[i+j] * ty[2] + a[i+j+k] * ty[3];
				a[i + j] = tmp0, a[i + j + k] = tmp1;
			}
}
