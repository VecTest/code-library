#include <bits/stdc++.h>

/*
大致思路：
平衡树 + 懒标签

提交地址：
https://www.luogu.com.cn/problem/P4146
*/

const int N = 50000;

struct Treap {
    const int INF = 2e9;

    int c, t;
    int l[N + 1], r[N + 1];
    int v[N + 1], d[N + 1];

    int s[N + 1], m[N + 1];

    bool f[N + 1];
    int g[N + 1];

    Treap() {
        c = t = 0;
        l[t] = r[t] = 0;
        v[t] = m[t] = -INF;
        d[t] = 0;
        s[t] = 0;
        f[t] = false;
        g[t] = 0;
        srand(20071017);
    }

    int add(int w) {
        t++;
        l[t] = r[t] = 0;
        v[t] = m[t] = w;
        d[t] = rand();
        s[t] = 1;
        f[t] = false;
        g[t] = 0;
        return t;
    }

    void pull(int p) {
        s[p] = s[l[p]] + s[r[p]] + 1;
        m[p] = std::max({v[p], m[l[p]], m[r[p]]});
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
        if (g[p]) {
            if (l[p]) {
                g[l[p]] += g[p];
                v[l[p]] += g[p];
                m[l[p]] += g[p];
            }
            if (r[p]) {
                g[r[p]] += g[p];
                v[r[p]] += g[p];
                m[r[p]] += g[p];
            }
            g[p] = 0;
        }
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

    void add(int lx, int rx, int delta) {
        int x, y, z;
        split(c, rx, x, z);
        split(x, lx - 1, x, y);
        assert(y);
        g[y] += delta;
        v[y] += delta;
        m[y] += delta;
        c = merge(x, merge(y, z));
    }

    void reverse(int lx, int rx) {
        int x, y, z;
        split(c, rx, x, z);
        split(x, lx - 1, x, y);
        assert(y);
        f[y] ^= 1;
        c = merge(x, merge(y, z));
    }

    int get_max(int lx, int rx) {
        int x, y, z;
        split(c, rx, x, z);
        split(x, lx - 1, x, y);
        int ans = m[y];
        c = merge(x, merge(y, z));
        return ans;
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
	for (int i = 0; i < n; i++) {
		t.insert(0);
	}
	for (int i = 0; i < m; i++) {
		int o, l, r, x;
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d%d%d", &l, &r, &x);
			t.add(l, r, x);
		} else if (o == 2) {
			scanf("%d%d", &l, &r);
			t.reverse(l, r);
		} else if (o == 3) {
			scanf("%d%d", &l, &r);
			printf("%d\n", t.get_max(l, r));
		}
	}

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}