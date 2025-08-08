template <typename T>
constexpr T qpow(T x, u64 y) {
	T ans = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) ans *= x;
	return ans;
}
template <u32 mod>
struct Mint {
	u32 val;
	constexpr Mint () = default;
	constexpr Mint (auto x) : val(norm(x, mod)) { }
	static constexpr u32 norm(auto x, u32 m) {
		return x%=int(m), x<0&&(x+=m), x;
	}
	constexpr Mint pow(auto b) {
		return val ? qpow(*this, norm(b, mod-1)) : 0;
	}
	constexpr Mint inv() { return pow(-1); }
	friend constexpr Mint operator+ (Mint a, Mint b) { return a.val + b.val; }
	friend constexpr Mint operator- (Mint a) { return mod-a.val; }
	friend constexpr Mint operator- (Mint a, Mint b) { return a + (-b); }
	friend constexpr Mint operator* (Mint a, Mint b) { return u64(a.val) * b.val; }
	friend constexpr Mint operator/ (Mint a, Mint b) { return b.inv() * a; }
	friend constexpr Mint& operator+= (Mint &a, Mint b) { return a = a + b; }
	friend constexpr Mint& operator-= (Mint &a, Mint b) { return a = a - b; }
	friend constexpr Mint& operator*= (Mint &a, Mint b) { return a = a * b; }
	friend constexpr Mint& operator/= (Mint &a, Mint b) { return a = a / b; }
	friend constexpr Mint& operator++ (Mint &a) { return a += 1; }
	friend constexpr Mint& operator-- (Mint &a) { return a -= 1; }
	friend auto& operator<< (auto &s, Mint a) { return s << a.val; }
};
using Z = Mint<998'244'353>;
