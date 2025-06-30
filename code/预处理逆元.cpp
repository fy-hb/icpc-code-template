inv[1] = 1; REP(i, 2, n) inv[i] = u64(mod - mod / i) * inv[mod % i] % mod;
