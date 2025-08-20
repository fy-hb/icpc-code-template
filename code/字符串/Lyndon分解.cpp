vector<int> duval(const auto &s) {
	int i = 0, j, k, n = s.size();
	vector<int> ans = {0};
	while (i < n) {
		for (j = i, k = i + 1; j < n && k < n && s[j] <= s[k]; k ++)
			j = s[j] == s[k] ? j + 1 : i;
		for (; i <= j; i += k - j) ans.push_back(i + k - j);
	}
	return ans;
} // [ans[i], ans[i+1]), 0-index
