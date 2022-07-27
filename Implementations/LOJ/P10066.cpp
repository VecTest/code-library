#include <bits/stdc++.h>

/*
大致思路：
最小生成树 + 超源点

提交地址：
https://loj.ac/p/10066
*/

const int N = 300;

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

int Kruskal(int n, std::vector<Edge> &e) {
	std::sort(e.begin(), e.end());

	DSU dsu(n);
	int ans = 0, c = 0;
	for (int i = 0; i < (int) e.size(); i++) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		if (!dsu.same(u, v)) {
			ans += e[i].w;
			dsu.merge(u, v);
			if (++c == n - 1) {
				break;
			}
		}
	}

	assert(c == n - 1);
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);

	int p[N];
	std::vector<Edge> e;
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
		e.push_back({i, n, p[i]});
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int w;
			scanf("%d", &w);
			if (i < j) {
				e.push_back({i, j, w});
			}
		}
	}

	int ans = Kruskal(n + 1, e);
	printf("%d\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}