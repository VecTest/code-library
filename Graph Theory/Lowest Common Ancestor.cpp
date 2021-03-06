#include <bits/stdc++.h>

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

int length(int u, int v) {
	return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

int distance(int u, int v) {
	return dist[u] + dist[v] - 2 * dist[LCA(u, v)];
}