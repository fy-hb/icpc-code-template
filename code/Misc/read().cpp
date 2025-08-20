int read() { // 换成 getchar_unlocked 可加快速度
	int x = 0, w = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') w = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	return x * w;
}
