#include <bits/stdc++.h>

/*
大致思路：
最小生成树

提交地址：
https://loj.ac/p/10065
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
	double w;

	bool operator < (const Edge &x) const {
		return w < x.w;
	}
};

struct Node {
	int x, y;
};

double Kruskal(int n, int k, std::vector<Edge> &e) {
	std::sort(e.begin(), e.end());

	DSU dsu(n);
	double ans = 0;
	int c = 0;
	for (int i = 0; i < (int) e.size(); i++) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		if (!dsu.same(u, v)) {
			ans = e[i].w;
			dsu.merge(u, v);
			if (++c >= n - k) {
				break;
			}
		}
	}
	return ans;
}

double d(Node a, Node b) {
	double delta = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return sqrt(delta);
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	k = std::min(n, k);

	std::vector<Node> a(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}

	std::vector<Edge> e;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			e.push_back({i, j, d(a[i], a[j])});
		}
	}

	double ans = Kruskal(n, k, e);
	printf("%.2lf\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}