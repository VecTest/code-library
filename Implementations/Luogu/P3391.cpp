#include <bits/stdc++.h>

/*
大致思路：
平衡树 + 懒标签

提交地址：
https://www.luogu.com.cn/problem/P3391
*/

const int N = 1e5;

struct Treap {
	int c, t;
	int l[N + 1], r[N + 1];
	int v[N + 1], d[N + 1];
	int s[N + 1];

	bool f[N + 1];

	Treap() {
		c = t = 0;
		l[t] = r[t] = 0;
		v[t] = d[t] = 0;
		s[t] = 0;

		f[t] = false;
		srand(20071017);
	}

	void pull(int p) {
		s[p] = s[l[p]] + s[r[p]] + 1;
	}

	void push(int p) {
		if (f[p]) {
			if (l[p]) {
				f[l[p]] ^= 1;
			}
			if (r[p]) {
				f[r[p]] ^= 1;
			}
			std::swap(l[p], r[p]);
			f[p] = false;
		}
	}

	int add(int w) {
		t++;
		l[t] = r[t] = 0;
		v[t] = w;
		d[t] = rand();
		s[t] = 1;

		f[t] = false;
		return t;
	}

	void split(int p, int k, int &x, int &y) {
		if (p == 0) {
			x = y = 0;
		} else {
			push(p);
			if (s[l[p]] + 1 <= k) {
				x = p;
				split(r[x], k - (s[l[p]] + 1), r[x], y);
			} else {
				y = p;
				split(l[y], k, x, l[y]);
			}
			pull(p);
		}
	}

	int merge(int x, int y) {
		if (x == 0 || y == 0) {
			return x | y;
		} else {
			if (d[x] > d[y]) {
				push(x);
				r[x] = merge(r[x], y);
				pull(x);
				return x;
			} else {
				push(y);
				l[y] = merge(x, l[y]);
				pull(y);
				return y;
			}
		}
	}

	void insert(int w) {
		c = merge(c, add(w));
	}

	void modify(int lx, int rx) {
		int x, y, z;
		split(c, rx, x, z);
		split(x, lx - 1, x, y);
		assert(y);
		f[y] ^= 1;
		c = merge(x, merge(y, z));
	}

	void traverse(int p) {
		if (p) {
			push(p);
			traverse(l[p]);
			printf("%d ", v[p]);
			traverse(r[p]);
		}
	}

	void print() {
		traverse(c);
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	Treap t;
	for (int i = 1; i <= n; i++) {
		t.insert(i);
	}
	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		t.modify(l, r);
	}
	t.print();

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}