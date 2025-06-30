int select(int k) { // 最后一个前缀和 <= k 的位置
	int x = 0, cur = 0;
	for (int i = 1<<__lg(n); i; i /= 2)
		if (x + i <= n && cur + tree[x+i] <= k)
			x += i, cur = cur + tree[x];
	return x;
}
