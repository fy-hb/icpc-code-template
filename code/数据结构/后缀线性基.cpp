template <typename T = u32, int siz = 32>
struct Basis {
	array<T, siz> b;
	array<int, siz> t;
	void insert(T v, int tt) {
		REV(j, siz-1, 0) {
			if (v >> j & 1) {
				if (tt > t[j]) {
					swap(v, b[j]);
					swap(tt, t[j]);
				}
				v ^= b[j];
			}
		}
	}
	T query(int tt) {
		T ans = 0;
		REV(j, siz-1, 0) {
			if (t[j] < tt) continue;
			if ((ans ^ b[j]) > ans) ans ^= b[j];
		}
		return ans;
	}
	int check(T tar, int tt) {
		REV(j, siz-1, 0) {
			if (tar >> j & 1) {
				if (t[j] < tt) return 0;
				if (!b[j]) return 0;
				tar ^= b[j];
			}
		}
		return 1;
	}
	friend Basis operator+ (Basis a, Basis b) {
		REP(i, 0, siz-1) {
			a.insert(b.b[i], b.t[i]);
		}
		return a;
	};
};
