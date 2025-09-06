int getday(int y, int m, int d) {
	if (m <= 2) y --, m += 12;
	return (y*365 + y/4 - y/100 + y/400 + ((m-3)*153 + 2) / 5 + d - 307);
}
array<int, 3> getdate(int n) {
	n += 429 + ((4 * n + 1227) / 146097 + 1) * 3 / 4;
	int y, m, d;
	y = (4 * n - 489) / 1461;
	n -= y * 1461 / 4;
	m = (5 * n - 1) / 153;
	d = n - m * 153 / 5;
	if (--m > 12) m -= 12, ++y;
	return {y, m, d};
}
