#include <bits/stdc++.h>

/*
大致思路：
最小生成树

提交地址：
https://loj.ac/p/10067
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
	int w;

	bool operator < (const Edge &x) const {
		return w < x.w;
	}
};

int main() {
	int n;
	scanf("%d", &n);

	std::vector<Edge> e(n - 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--;
		v--;
		e[i] = {u, v, w};
	}
	std::sort(e.begin(), e.end());

	DSU dsu(n);
	long long ans = 0;
	for (int i = 0; i < n - 1; i++) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		int w = e[i].w;
		ans += w;
		ans += (long long) (w + 1) * (dsu.size(u) * dsu.size(v) - 1);
		dsu.merge(u, v);
	}
	printf("%lld\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}