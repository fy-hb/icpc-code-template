istream& operator>>(istream& cin, i128& x) {
	i128 w = 1, v = 0;
	string s; cin >> s;
	for (auto i : s) {
		if (i == '-') w = -1;
		else v = v * 10 + (i - '0');
	}
   return x = w * v, cin;
}
ostream& operator<<(ostream& cout, i128 x) {
	if (x == 0) return cout << 0;
	if (x < 0) cout << '-', x = -x;
	string s;
	while (x) s += '0' + x % 10, x /= 10;
	reverse(s.begin(), s.end());
	return cout << s;
}
