#include <bits/stdc++.h>

/*
大致思路：
最小生成树 + 二分增量

提交地址：
https://loj.ac/p/10069
*/

struct DisjointSetsUnion {
	std::vector<int> p, s;
	DisjointSetsUnion(int n): p(n), s(n, 1) {
		std::iota(p.begin(), p.end(), 0);
	}
	DisjointSetsUnion() {

	}
	int find(int x) {
		return p[x] = (x == p[x] ? x : find(p[x]));
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		if (s[x] > s[y]) {
			std::swap(x, y);
		}
		s[y] += s[x];
		p[x] = y;
		return true;
	}
	int size(int x) {
		return s[find(x)];
	}
};
using DSU = DisjointSetsUnion;

struct Edge {
	int u, v;
	int w, c;

	bool operator < (const Edge &x) const {
		return w < x.w || (w == x.w && c < x.c);
	}
};

std::pair<int, int> Kruskal(int n, int d, std::vector<Edge> &e) {
	for (int i = 0; i < (int) e.size(); i++) {
		if (e[i].c == 0) {
			e[i].w += d;
		}
	}
	std::sort(e.begin(), e.end());

	DSU dsu(n);
	int ans = 0, take = 0;
	int c = 0;
	for (int i = 0; i < (int) e.size(); i++) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		if (!dsu.same(u, v)) {
			ans += e[i].w;
			take += e[i].c ^ 1;
			dsu.merge(u, v);
			if (++c == n - 1) {
				break;
			}
		}
	}

	assert(c == n - 1);
	for (int i = 0; i < (int) e.size(); i++) {
		if (e[i].c == 0) {
			e[i].w -= d;
		}
	}
	return {ans, take};
}

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);

	std::vector<Edge> e(m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].c);
	}

	int l = -100, r = 100, ans = -1;
	while (r - l > 1) {
		int d = (l + r) / 2;
		std::pair<int, int> p = Kruskal(n, d, e);
		if (p.second >= k) {
			ans = p.first - d * k;
			l = d;
		} else {
			r = d;
		}
	}
	assert(ans != -1);
	printf("%d\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}