#include <bits/stdc++.h>

/*
大致思路：
倍增 + 最近公共祖先

提交地址：
https://loj.ac/p/10134
*/

const int N = 1e5, LOG = 16;
const int S = 0, P = -1;

struct Edge {
	int v, w;
};

std::vector<std::vector<Edge>> e;
int f[N][LOG + 1];
int depth[N], dist[N];

void dfs(int u, int p, int l, int d) {
	f[u][0] = p;
	depth[u] = l;
	dist[u] = d;
	for (int i = 0; i < (int) e[u].size(); i++) {
		int v = e[u][i].v, w = e[u][i].w;
		if (v != p) {
			dfs(v, u, l + 1, d + w);
		}
	}
}

void process(int n, int s) {
	dfs(s, P, 0, 0);
	for (int k = 0; k < LOG; k++) {
		for (int i = 0; i < n; i++) {
			if (f[i][k] < 0) {
				f[i][k + 1] = f[i][k];
			} else {
				f[i][k + 1] = f[f[i][k]][k];
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

int distance(int u, int v) {
	return dist[u] + dist[v] - 2 * dist[LCA(u, v)];
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	e = std::vector<std::vector<Edge>>(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--;
		v--;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	process(n, S);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--;
		v--;
		printf("%d\n", distance(u, v));
	}

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}