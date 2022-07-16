#include <bits/stdc++.h>

/*
大致思路：
分层图最短路

提交地址：
https://www.luogu.com.cn/problem/P2937
*/

const int N = 100;
const int INF = 1e9;

struct Edge {
	int v, w;
};

struct Vertex {
	int p, d;
	bool operator < (const Vertex &x) const {
		return d > x.d;
	}
};

std::vector<int> Dijkstra(int n, int s, std::vector<std::vector<Edge>> &e) {
	std::vector<int> d(n, INF);
	d[s] = 0;

	std::vector<bool> f(n, false);

	std::priority_queue<Vertex> q;
	q.push({s, d[s]});

	while (!q.empty()) {
		int u = q.top().p;
		q.pop();

		if (f[u]) {
			continue;
		}
		f[u] = true;

		for (int i = 0; i < (int) e[u].size(); i++) {
			int v = e[u][i].v, w = e[u][i].w;
			if (!f[v] && d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({v, d[v]});
			}
		}
	}

	return d;
}

int main() {
	int n, m;
	scanf("%d%d", &m, &n);

	int sx, sy;
	int ex, ey;
	sx = sy = ex = ey = -1;
	bool f = false;

	char g[N][N];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &g[i][j]);
			if (g[i][j] == 'C') {
				if (!f) {
					sx = i, sy = j;
					f = true;
				} else {
					ex = i, ey = j;
				}
			}
		}
	}
	assert(sx != -1 && sy != -1);
	assert(ex != -1 && ey != -1);

	std::vector<std::vector<Edge>> e(n * m * 2);
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (g[i][j] != '*' && g[i][j - 1] != '*') {
				e[i * m + j].push_back({i * m + (j - 1), 0});
				e[i * m + (j - 1)].push_back({i * m + j, 0});
			}
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j] != '*' && g[i - 1][j] != '*') {
				e[n * m + i * m + j].push_back({n * m + (i - 1) * m + j, 0});
				e[n * m + (i - 1) * m + j].push_back({n * m + i * m + j, 0});
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j] == '.') {
				e[i * m + j].push_back({n * m + i * m + j, 1});
				e[n * m + i * m + j].push_back({i * m + j, 1});
			} else if (g[i][j] == 'C') {
				e[i * m + j].push_back({n * m + i * m + j, 0});
				e[n * m + i * m + j].push_back({i * m + j, 0});
			}
		}
	}

	std::vector<int> d = Dijkstra(n * m * 2, sx * m + sy, e);
	printf("%d\n", d[ex * m + ey]);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}