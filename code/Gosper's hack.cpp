struct Comb { // for (auto i : Comb(n, m))
	int n, m; // 1 <= n && n <= 64 && 1 <= m && m <= n
	struct iterator {
		u64 x;
		u64 operator*() { return x; }
		bool operator==(const iterator& oth) const { return x == oth.x; }
		auto& operator++() {
			u64 b = x & -x, t = x + b, c = t & -t, m = (c / b >> 1) - 1;
			return x = t | m, *this;
		}
	};
	iterator begin() const { return iterator{(1ULL << m) - 1}; }
	iterator end() const { return ++(iterator{((1ULL << m) - 1) << (n - m)}); }
};
