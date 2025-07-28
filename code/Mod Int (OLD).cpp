constexpr int mod = 998'244'353;
constexpr int qpow(int x, int y, int m = mod, int ans = 1) {
	for (; y; y >>= 1, x = (u64) x * x % m)
		if (y & 1) ans = (u64) ans * x % m;
	return ans; }
constexpr int Normal(i64 x, int m = mod) { return x%=m, x<0&&(x+=m), x; }
struct Mint { int val; constexpr Mint(i64 x = 0) : val(Normal(x)) {} };
constexpr Mint Pow(Mint a, i64 p) { return qpow(a.val, Normal(p, mod-1)); }
constexpr Mint Inv(Mint a) { return Pow(a, -1); }
constexpr Mint operator- (Mint a) { return mod - a.val; }
constexpr Mint operator+ (Mint a, Mint b) { return a.val + b.val; }
constexpr Mint operator- (Mint a, Mint b) { return a.val - b.val; }
constexpr Mint operator* (Mint a, Mint b) { return (u64) a.val * b.val; }
constexpr Mint operator/ (Mint a, Mint b) { return a * Inv(b); }
constexpr Mint& operator+= (Mint &a, Mint b) { return a = a + b; }
constexpr Mint& operator-= (Mint &a, Mint b) { return a = a - b; }
constexpr Mint& operator*= (Mint &a, Mint b) { return a = a * b; }
constexpr Mint& operator/= (Mint &a, Mint b) { return a = a / b; }
constexpr Mint& operator++ (Mint &a) { return a += 1; }
constexpr Mint& operator-- (Mint &a) { return a -= 1; }
constexpr Mint operator++ (Mint &a, int) { auto b = a; return a += 1, b; }
constexpr Mint operator-- (Mint &a, int) { auto b = a; return a -= 1, b; }
template <typename S> S& operator<< (S &s, Mint a) { return s << a.val; }
constexpr bool operator== (Mint a, Mint b) { return a.val == b.val; }
constexpr Mint operator""_M (unsigned long long x) { return x % mod; }
