#include <bits/stdc++.h>

/*
大致思路：
最小生成树 + 最短路

提交地址：
https://loj.ac/p/10065
*/

const int S = 0;
const int INF = 1e9;
const int MOD = std::numeric_limits<int>::max();

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
	std::priority_queue<Vertex> q;
	std::vector<bool> f(n, false);

	d[s] = 0;
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
	scanf("%d%d", &n, &m);

	std::vector<std::vector<Edge>> e(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--;
		v--;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	std::vector<int> d = Dijkstra(n, S, e);

	std::vector<int> c(n, 0);
	c[S] = 1;
	for (int u = 0; u < n; u++) {
		for (int i = 0; i < (int) e[u].size(); i++) {
			int v = e[u][i].v, w = e[u][i].w;
			if (d[v] == d[u] + w) {
				c[v]++;
			}
		}
	}

	int ans = 1;
	for (int i = 0; i < n; i++) {
		ans = (long long) ans * c[i] % MOD;
	}
	printf("%d\n", ans);

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}