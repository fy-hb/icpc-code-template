REP(i, 2, n) inv[i] = i==1 ? 1 : inv[mod % i] * (mod - mod / i);
