#include <bits/stdc++.h>

const int N = 1e4;
const int INF = std::numeric_limits<int>::max();

struct Edge {
    int v, w;
};

int dist[N];

void Bellman_Ford(int n, int s, std::vector<std::vector<Edge>> &e) {
    std::queue<int> q;
    bool f[N];

    std::fill(dist, dist + n, INF);
    dist[s] = 0;
    q.push(s);
    std::fill(f, f + n, false);
    f[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        f[u] = false;

        for (int i = 0; i < (int) e[u].size(); i++) {
            int v = e[u][i].v, w = e[u][i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!f[v]) {
                    q.push(v);
                    f[v] = true;
                }
            }
        }
    }
}