#include <bits/stdc++.h>

const int N = 1e5;
const int INF = 2e9;

struct Treap {
	int c, t;
	int l[N + 1], r[N + 1];
	int v[N + 1], d[N + 1];
	int s[N + 1];

	Treap() {
		c = t = 0;
		l[t] = r[t] = 0;
		v[t] = d[t] = 0;
		s[t] = 0;
		srand(20071017);
	}

	void pull(int p) {
		s[p] = s[l[p]] + s[r[p]] + 1;
	}

	int add(int w) {
		t++;
		l[t] = r[t] = 0;
		v[t] = w;
		d[t] = rand();
		s[t] = 1;
		return t;
	}

	void split(int p, int w, int &x, int &y) {
		if (p == 0) {
			x = y = 0;
		} else {
			if (v[p] <= w) {
				x = p;
				split(r[x], w, r[x], y);
			} else {
				y = p;
				split(l[y], w, x, l[y]);
			}
			pull(p);
		}
	}

	int merge(int x, int y) {
		if (x == 0 || y == 0) {
			return x | y;
		} else {
			if (d[x] > d[y]) {
				r[x] = merge(r[x], y);
				pull(x);
				return x;
			} else {
				l[y] = merge(x, l[y]);
				pull(y);
				return y;
			}
		}
	}

	void insert(int w) {
		int x, y;
		split(c, w - 1, x, y);
		c = merge(x, merge(add(w), y));
	}

	void erase(int w) {
		int x, y, z;
		split(c, w, x, z);
		split(x, w - 1, x, y);
		assert(y);
		y = merge(l[y], r[y]);
		c = merge(x, merge(y, z));
	}

	int get_rank(int w) {
		int x, y;
		split(c, w - 1, x, y);
		int ans = s[x] + 1;
		c = merge(x, y);
		return ans;
	}

	int get_value(int k) {
		int p = c;
		while (p) {
			if (s[l[p]] >= k) {
				p = l[p];
			} else if (s[l[p]] + 1 == k) {
				return v[p];
			} else {
				k -= (s[l[p]] + 1);
				p = r[p];
			}
		}
		assert(false);
	}

	int get_precursor(int w) {
		int p = c;
		int ans = -INF;
		while (p) {
			if (v[p] < w) {
				ans = v[p];
				p = r[p];
			} else {
				p = l[p];
			}
		}
		assert(ans > -INF);
		return ans;
	}

	int get_successor(int w) {
		int p = c;
		int ans = INF;
		while (p) {
			if (v[p] > w) {
				ans = v[p];
				p = l[p];
			} else {
				p = r[p];
			}
		}
		assert(ans < INF);
		return ans;
	}
};