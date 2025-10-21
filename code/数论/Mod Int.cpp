template <typename T>
constexpr T qpow(T x, u64 y) {
	T ans = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) ans *= x;
	return ans;
}
template <u32 P>
struct Mint {
	u32 val;
	static constexpr u32 norm(u32 x, u32 p) {
		return x >= p ? x - p : x;
	}
	static constexpr u32 mod(auto x, u32 p) {
		return x < 0 ? norm(p - u64(-x) % p, p) : x % p;
	}
	static constexpr u32 mulmod(u32 x, u32 y, u32 p) {
		return u64(x) * y % p;
	}
	constexpr Mint () = default;
	constexpr Mint (auto x) : val(mod(x, P)) { }
	constexpr Mint pow(auto b) const {
		return val ? qpow(*this, mod(b, P-1)) : 0;
	}
	constexpr Mint inv() const { return pow(-1); }
	friend constexpr Mint operator- (Mint a) {
		return a.val = norm(P - a.val, P), a;
	}
	constexpr Mint& operator+= (Mint b) {
		return val = norm(val + b.val, P), *this;
	}
	constexpr Mint& operator-= (Mint b) {
		return val = norm(val + P - b.val, P), *this;
	}
	constexpr Mint& operator*= (Mint b) {
		return val = mulmod(val, b.val, P), *this;
	}
	constexpr Mint& operator/= (Mint b) { return *this *= b.inv(); }
	friend constexpr Mint operator+ (Mint a, Mint b) { return a += b; }
	friend constexpr Mint operator- (Mint a, Mint b) { return a -= b; }
	friend constexpr Mint operator* (Mint a, Mint b) { return a *= b; }
	friend constexpr Mint operator/ (Mint a, Mint b) { return a /= b; }
	friend constexpr Mint& operator++ (Mint &a) { return a += 1; }
	friend constexpr Mint& operator-- (Mint &a) { return a -= 1; }
	friend auto& operator<< (auto &s, Mint a) { return s << a.val; }
};
using Z = Mint<1'000'000'007>;
