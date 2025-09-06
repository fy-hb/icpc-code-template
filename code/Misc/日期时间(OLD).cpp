int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
using Date = array<int, 3>;
inline int leap(int y) {
	return 1 ^ bool(y % 4) ^ bool(y % 100) ^ bool(y % 400);
}
inline int legal(Date dd) {
	auto [y, m, d] = dd;
	if (m < 0 || m > 12) return 0;
	return d > 0 && d <= days[m - 1] + bool(m==2&&leap(y));
}
int weekday(Date dd) {
	auto [y, m, d] = dd;
	int tm = m >= 3 ? (m - 2) : (m + 10);
	int ty = m >= 3 ? y : (y - 1);
	return (ty + ty / 4 - ty / 100 + ty / 400 + (int)(2.6 * tm - 0.2) + d) % 7;
}
int date2int(Date dd) {
	auto [y, m, d] = dd;
	int ret = y * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	days[1] += leap(y);
	for (int i = 0; i < m - 1; ret += days[i++]);
	days[1] = 28;
	return ret + d;
}
Date int2date(int tt) {
	int y, m, d;
	y = tt / 146097 * 400;
	for (tt %= 146097; tt >= 365 + leap(y); tt -= 365 + leap(y), y++);
	days[1] += leap(y);
	for (m = 1; tt >= days[m - 1]; tt -= days[m - 1], m++);
	days[1] = 28;
	return {y, m, tt + 1};
}
