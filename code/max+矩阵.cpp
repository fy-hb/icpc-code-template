template <typename Ty>
constexpr void chmax(Ty &a, Ty b) {
	if (b > a) a = b;
}
template <size_t N, typename T = i64>
using Mat = array<array<T, N>, N>;
template <size_t N, typename T>
constexpr Mat<N, T> operator* (const Mat<N, T> &a, const Mat<N, T> &b) {
	Mat<N, T> res {};
	REP(i, 0, N-1) REP(k, 0, N-1) res[i][k] = -1e16;
	REP(i, 0, N-1) REP(j, 0, N-1) REP(k, 0, N-1)
		chmax(res[i][k], a[i][j] + b[j][k]);
	return res;
}
