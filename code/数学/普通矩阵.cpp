template <size_t N, size_t M, typename T = i64>
using Mat = array<array<T, M>, N>;

template <size_t N, size_t M, typename T>
Mat<N, M, T> operator+ (const Mat<N, M, T> &a, const Mat<N, M, T> &b) {
	Mat<N, M, T> res {};
	REP(i, 0, N-1) REP(j, 0, M-1) res[i][j] = a[i][j] + b[i][j];
	return res;
}
template <size_t N, size_t M, typename T>
Mat<N, M, T> operator- (const Mat<N, M, T> &a, const Mat<N, M, T> &b) {
	Mat<N, M, T> res {};
	REP(i, 0, N-1) REP(j, 0, M-1) res[i][j] = a[i][j] - b[i][j];
	return res;
}
template <size_t N, size_t M, size_t K, typename T>
constexpr Mat<N, K, T> operator* (const Mat<N, M, T> &a, const Mat<M, K, T> &b) {
	Mat<N, K, T> res {};
	REP(i, 0, N-1) REP(j, 0, M-1) REP(k, 0, K-1)
		res[i][k] += a[i][j] * b[j][k];
	return res;
}
