array<int, 26> ch[N];
int s[N], fail[N], len[N], top[N], diff[N], siz, cnt, p;
int newnode(int l) {
	int x = ++cnt;
	ch[x] = {}; fail[x] = top[x] = diff[x] = 0; len[x] = l;
	return x;
}
void init() {
	siz = p = 0, s[0] = cnt = -1;
	newnode(0), newnode(-1), fail[0] = 1;
}
int getfail(int x) {
	while (s[siz - len[x] - 1] != s[siz]) x = fail[x];
	return x;
}
void push(char c) {
	s[++siz] = c, p = getfail(p);
	if (!ch[p][c]) {
		int x = newnode(len[p] + 2);
		fail[x] = ch[getfail(fail[p])][c];
		ch[p][c] = top[x] = x;
		diff[x] = len[x] - len[fail[x]];
		if (diff[x] == diff[fail[x]])
			top[x] = top[fail[x]];
	}
	p = ch[p][c];
}
for (int x = p; x > 1; x = fail[top[x]]) {
	sum[x] = dp[i - len[top[x]]];
	if (x != top[x]) sum[x] += sum[fail[x]];
	dp[i] += sum[x];
}
