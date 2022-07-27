#include <bits/stdc++.h>

const int N = 1e5;
const int INF = std::numeric_limits<int>::max();

struct Edge {
	int v, w;
};

struct Vertex {
	int p, d;
	bool operator < (const Vertex &x) const {
		return d > x.d;
	}
};

int dist[N];

void Dijkstra(int n, int s, std::vector<std::vector<Edge>> &e) {
	std::priority_queue<Vertex> q;
	bool f[N];

	std::fill(dist, dist + n, INF);
	dist[s] = 0;
	q.push({s, dist[s]});
	std::fill(f, f + n, false);

	while (!q.empty()) {
		int u = q.top().p;
		q.pop();

		if (f[u]) {
			continue;
		}
		f[u] = true;

		for (int i = 0; i < (int) e[u].size(); i++) {
			int v = e[u][i].v, w = e[u][i].w;
			if (!f[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				q.push({v, dist[v]});
			}
		}
	}
}