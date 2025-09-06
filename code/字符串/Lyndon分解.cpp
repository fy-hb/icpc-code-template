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
auto minrep(auto s) {
	int k = 0, i = 0, j = 1, n = ssize(s);
	while (k < n && i < n && j < n) {
		if (s[(i + k) % n] == s[(j + k) % n]) k ++;
		else {
			(s[(i + k) % n] > s[(j + k) % n] ? i : j) += k + 1;
			i += (i == j), k = 0;
		}
	}
	rotate(s.begin(), s.begin() + min(i, j), s.end());
	return s;
}
