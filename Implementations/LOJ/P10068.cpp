#include <bits/stdc++.h>

/*
大致思路：
次小生成树
倍增 + 最近公共祖先 + 最小生成树

提交地址：
https://loj.ac/p/10068
*/

const int N = 500, LOG = 9;
const int M = 1e4;
const int S = 0, P = -1;
const int INF = 1e9;

struct DisjointSetsUnion {
	std::vector<int> p, s;
	DisjointSetsUnion(int n): p(n), s(n, 1) {
		std::iota(p.begin(), p.end(), 0);
	}
	DisjointSetsUnion() {

	}
	int get(int x) {
		return p[x] = (x == p[x] ? x : get(p[x]));
	}
	bool same(int x, int y) {
		return get(x) == get(y);
	}
	bool merge(int x, int y) {
		x = get(x);
		y = get(y);
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
		return s[get(x)];
	}
};
using DSU = DisjointSetsUnion;

struct Edge {
	int u, v, w;

	bool operator < (const Edge &x) const {
		return w < x.w;
	}
};

int n, m;

std::vector<Edge> e[N];
int f[N][LOG + 1], g[N][LOG + 1][2];
int depth[N];

bool vis[M];
Edge a[M];

long long Kruskal() {
	std::sort(a, a + m);
	DSU dsu(n);
	long long ans = 0;
	int c = 0;
	for (int i = 0; i < m; i++) {
		int uu = a[i].u, vv = a[i].v, ww = a[i].w;
		int u = dsu.get(uu), v = dsu.get(vv);
		if (u == v) {
			continue;
		}
		e[uu].push_back({uu, vv, ww});
		e[vv].push_back({vv, uu, ww});
		vis[i] = true;
		ans += ww;
		dsu.merge(u, v);
		if (++c == n - 1) {
			break;
		}
	}
	assert(c == n - 1);
	return ans;
}

void dfs(int u, int p, int l, int k) {
	f[u][0] = p;
	g[u][0][0] = k;
	g[u][0][1] = -INF;
	depth[u] = l;
	for (int i = 0; i < (int) e[u].size(); i++) {
		int v = e[u][i].v, w = e[u][i].w;
		if (v != p) {
			dfs(v, u, l + 1, w);
		}
	}
}

void process() {
	dfs(S, P, 0, -INF);
	for (int k = 0; k < LOG; k++) {
		for (int i = 0; i < n; i++) {
			if (f[i][k] < 0) {
				f[i][k + 1] = f[i][k];
				g[i][k + 1][0] = g[i][k][0];
				g[i][k + 1][1] = g[i][k][1];
			} else {
				f[i][k + 1] = f[ f[i][k] ][k];

				int x = g[i][k][0];
				int y = g[ f[i][k] ][k][0];
				g[i][k + 1][0] = std::max(x, y);
				if (x == y) {
					g[i][k + 1][1] = std::max(g[i][k][1], g[ f[i][k] ][k][1]);
				} else if (x < y) {
					g[i][k + 1][1] = std::max(x, g[ f[i][k] ][k][1]);
				} else {
					g[i][k + 1][1] = std::max(g[i][k][1], y);
				}
			}
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	for (int k = LOG; k >= 0; k--) {
		if ((depth[v] - depth[u]) >> k & 1) {
			v = f[v][k];
		}
	}
	if (u == v) {
		return u;
	}
	for (int k = LOG; k >= 0; k--) {
		if (f[u][k] != f[v][k]) {
			u = f[u][k];
			v = f[v][k];
		}
	}
	return f[u][0];
}

int get_max(int u, int v, int w) {
	int ans = -INF;

	for (int k = LOG; k >= 0; k--) {
		if (f[u][k] < 0) {
			continue;
		}
		if (depth[f[u][k]] >= depth[v]) {
			int x = g[u][k][0], y = g[u][k][1];
			if (x < w) {
				ans = std::max(ans, x);
			} else {
				ans = std::max(ans, y);
			}
			u = f[u][k];
		}
	}

	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--;
		v--;
		a[i] = {u, v, w};
	}

	long long MST = Kruskal();
	long long ans = (long long) N * INF;
	process();
	for (int i = 0; i < m; i++) {
		if (vis[i]) {
			continue;
		}
		int u = a[i].u, v = a[i].v, w = a[i].w;
		int k = LCA(u, v);
		int t = std::max(get_max(u, k, w), get_max(v, k, w));
		ans = std::min(ans, MST + (w - t));
	}
	printf("%lld\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}