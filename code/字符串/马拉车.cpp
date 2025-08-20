void manacher(int sz) {
	int R = 0, mid = 0;
	REP(i, 1, sz-1) {
		p[i] = R > i ? min(p[2*mid-i], R-i) : 1;
		while (s1[i+p[i]] == s1[i-p[i]]) p[i]++;
		if (i + p[i] > R) R = i + p[i], mid = i;
	}
}
int is_pal(int l, int r) { return p[l+r] > r - l; }
/*
0 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M [index]
 1   1   1   1   1   11  1   1   1   1   1
^ . a . b . c . b . a . a . b . c . b . a . @
   2   2   6   2   2   2   2   6   2   2
*/
