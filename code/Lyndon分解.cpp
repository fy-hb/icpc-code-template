vector<int> duval(const vector<int> &s) {
	int i = 0, j, k, n = s.size();
	vector<int> ans = {-1};
	while (i < n) {
		j = i, k = i + 1;
		while (j < n && k < n && s[j] <= s[k])
			j = s[j] == s[k] ? j + 1 : i, k ++;
		while (i <= j) ans.push_back(i + k - j - 1), i += k - j;
	}
	return ans;
} // [ans[i]+1, ans[i+1]]
