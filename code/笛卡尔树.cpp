vector<array<int, 2>> build(vector<int> a, int n) {
	stack<int> st; st.push(0);
	vector<array<int, 2>> tree(n + 1);
	REP(i, 1, n) { // 大根堆则是 <
		while (ssize(st) > 1 && (a[st.top()] > a[i])) st.pop();
		tree[i][0] = tree[st.top()][1];
		tree[st.top()][1] = i;
		st.push(i);
	}
	return tree;
}
