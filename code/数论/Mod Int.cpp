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
		return x%=int(m), (x<0)&&(x+=m), x;
	}
	constexpr Mint pow(auto b) {
		return val ? qpow(*this, norm(b, mod-1)) : 0;
	}
	constexpr Mint inv() { return pow(-1); }
	friend constexpr Mint operator- (Mint a) {
		return a.val && (a.val=mod-a.val), a;
	}
	constexpr Mint& operator+= (Mint b) {
		return val+=b.val, (val>=mod)&&(val-=mod), *this;
	}
	constexpr Mint& operator*= (Mint b) {
		return val = u64(val)*b.val%mod, *this;
	}
	constexpr Mint& operator-= (Mint b) { return *this += (-b); }
	constexpr Mint& operator/= (Mint b) { return *this *= b.inv(); }
	friend constexpr Mint operator+ (Mint a, Mint b) { return a += b; }
	friend constexpr Mint operator- (Mint a, Mint b) { return a -= b; }
	friend constexpr Mint operator* (Mint a, Mint b) { return a *= b; }
	friend constexpr Mint operator/ (Mint a, Mint b) { return a /= b; }
	friend constexpr Mint& operator++ (Mint &a) { return a += 1; }
	friend constexpr Mint& operator-- (Mint &a) { return a -= 1; }
	friend auto& operator<< (auto &s, Mint a) { return s << a.val; }
};
using Z = Mint<998'244'353>;
