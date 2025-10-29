constexpr int N = ((1 << 22));  // sieve_span
constexpr int M = ((N >> 7));   // sieve_words
constexpr int SIZ = ((3 * 5 * 7 * 11 * 13)); // wheel_size

u64 mask[64]; //mask[i] = 1ull << i
int primes[N / 20], mcnt; // !
u64 sieve[M];
u64 pattern[SIZ];
int all[5761455 + 10], pcnt;
int test(u64* s, int o) { return (s[o >> 6] & mask[o & 63]) == 0; }
void mark(u64* s, int o) { s[o >> 6] |= mask[o & 63]; }
void unmark(u64* s, int o) { s[o >> 6] &= ~mask[o & 63]; }

void pre_sieve() {
	memset(sieve, 0, sizeof(sieve));
	memset(pattern, 0, sizeof(pattern));
	for (int i = 3; i < 1024; i += 2)
		if (test(sieve, i >> 1))
			for (int j = (i*i)>>1; j < (1<<20); j += i)
				mark(sieve, j);
	mcnt = 0;
	REP(i, 8, (1<<20)-1)
		if (test(sieve, i)) primes[mcnt++] = (i<<1) + 1;
	// printf("m is %d\n", mcnt);
	for (int i = 1; i < SIZ * 64; i += 3) mark(pattern, i);
	for (int i = 2; i < SIZ * 64; i += 5) mark(pattern, i);
	for (int i = 3; i < SIZ * 64; i += 7) mark(pattern, i);
	for (int i = 5; i < SIZ * 64; i += 11) mark(pattern, i);
	for (int i = 6; i < SIZ * 64; i += 13) mark(pattern, i);
}
void update_sieve(int base) {
	int o = base % SIZ;
	o = (o + ((o * 105) & 127) * SIZ) >> 7;
	for (int i = 0, k; i < M; i += k, o = 0) {
		k = min(SIZ - o, M - i);
		memcpy(sieve + i, pattern + o, sizeof(*pattern) * k);
	}
	if (base == 0) { // mark 1 as not prime, and mark 3, 5, 7, 11, and 13 as prime
		sieve[0] |= mask[0];
		sieve[0] &= ~(mask[1] | mask[2] | mask[3] | mask[5] | mask[6]);
	}
	REP(i, 0, mcnt-1) {
		i64 j = primes[i] * primes[i];
		if (j > base + N - 1) break;
		if (j > base) j = (j - base) >> 1;
		else {
			j = primes[i] - base % primes[i];
			if ((j & 1) == 0) j += primes[i];
			j >>= 1;
		}
		while (j < N >> 1) {
			mark(sieve, j);
			j += primes[i];
		}
	}
}
//sieve [base, min(base+span, lim)]
void segment_sieve(int base, int lim) {
	update_sieve(base);
	int u = min(base + N, lim);
	REP(i, 0, M-1) {
		for (u64 o = ~sieve[i]; o; o -= o&-o) {
			int p = __builtin_ctzll(o);
			int u = base + (i << 7) + (p << 1) + 1;
			if (u >= lim) break;
			all[pcnt++] = u;
		}
	}
}
void fast_sieve(int lim) {
	mask[0] = 1ull;
	REP(i, 1, 63) mask[i] = mask[i-1] << 1;
	pre_sieve();
	all[pcnt++] = 2;
	int i = 0, now = 1;
	for (int base = 0; base < lim; base += N)
		segment_sieve(base, lim);
}
