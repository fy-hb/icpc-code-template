u64 xorshift(u64 x) { return x^=x<<13, x^=x>>7, x^=x<<17, x; }
u32 xorshift(u32 x) { return x^=x<<13, x^=x>>17, x^=x<<5, x; }
