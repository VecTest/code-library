#include <bits/stdc++.h>

const int INF = 1e9;
const int S = 0;

struct Edge {
	int v, w;
};

struct Vertex {
	int p, d;
	bool operator < (const Vertex &x) const {
		return d > x.d;
	}
};

int Prim(int n, std::vector<std::vector<Edge>> &e) {
	std::vector<int> d(n, INF);
	std::priority_queue<Vertex> q;
	std::vector<bool> f(n, false);

	d[S] = 0;
	q.push({S, d[S]});

	int ans = 0;
	int c = 0;
	while (!q.empty() && c < n) {
		int u = q.top().p, t = q.top().d;
		q.pop();

		if (f[u]) {
			continue;
		}
		f[u] = true;
		c++;
		ans += t;

		for (int i = 0; i < (int) e[u].size(); i++) {
			int v = e[u][i].v, w = e[u][i].w;
			if (!f[v] && d[v] > w) {
				d[v] = w;
				q.push({v, d[v]});
			}
		}
	}

	assert(c == n);
	return ans;
}