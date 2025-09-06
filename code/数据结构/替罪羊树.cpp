constexpr double alpha = 0.75;
int root[N], gc[N], tmp[N], top, cnt, tmpsiz;
struct {
	int ls, rs, val, cnt, siz0, siz1, siz2;
} tr[N];
int getnew() {
	int x = top ? gc[top--] : ++cnt;
	return tr[x] = {}, x;
}
void pushup(int x) {
	tr[x].siz0 = tr[tr[x].ls].siz0 + tr[tr[x].rs].siz0 + bool(tr[x].cnt);
	tr[x].siz1 = tr[tr[x].ls].siz1 + tr[tr[x].rs].siz1 + 1;
	tr[x].siz2 = tr[tr[x].ls].siz2 + tr[tr[x].rs].siz2 + tr[x].cnt;
}
int check(int x) {
	if (!tr[x].siz2) return 1;
	return alpha * tr[x].siz1 > max(tr[tr[x].ls].siz1, tr[tr[x].rs].siz1)
		&& alpha * tr[x].siz1 < tr[x].siz0;
}
void dfs(int x) {
	if (!x) return;
	dfs(tr[x].ls);
	if (tr[x].cnt) tmp[++tmpsiz] = x;
	else gc[++top] = x;
	dfs(tr[x].rs);
}
int build(int l, int r) {
	if (l > r) return 0;
	int mid = l + (r - l) / 2, x = tmp[mid];
	tr[x].ls = build(l, mid-1);
	tr[x].rs = build(mid+1, r);
	return pushup(x), x;
}
void rebuild(int &x) {
	tmpsiz = 0, dfs(x), x = build(1, tmpsiz);
}
void insert(int &x, int val) {
	if (!x) return x = getnew(), tr[x].val = val, tr[x].cnt = 1, pushup(x);
	if (tr[x].val == val) tr[x].cnt ++;
	else if (tr[x].val < val) insert(tr[x].rs, val);
	else insert(tr[x].ls, val);
	pushup(x);
	if (!check(x)) rebuild(x);
}
void delet(int &x, int val) {
	if (tr[x].val == val) tr[x].cnt --;
	else if (tr[x].val < val) delet(tr[x].rs, val);
	else delet(tr[x].ls, val);
	pushup(x);
	if (!check(x)) rebuild(x);
}
int getrank(int x, int val) {
	if (!x) return 0;
	if (tr[x].val >= val) return getrank(tr[x].ls, val);
	else return tr[tr[x].ls].siz2 + tr[x].cnt + getrank(tr[x].rs, val);
}
int findval(int x, int rnk) {
	while (x) {
		if (rnk <= tr[tr[x].ls].siz2) x = tr[x].ls;
		else if (rnk <= tr[tr[x].ls].siz2 + tr[x].cnt) break;
		else rnk -= tr[tr[x].ls].siz2 + tr[x].cnt, x = tr[x].rs;
	}
	return tr[x].val;
}
