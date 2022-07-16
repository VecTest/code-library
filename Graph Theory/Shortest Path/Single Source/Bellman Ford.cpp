#include <bits/stdc++.h>

struct Edge {
    int u, v;
    int w;
};

const int INF = std::numeric_limits<int>::max();
std::vector<int> Bellman_Ford(int n, int s, std::vector<Edge> &e) {
    std::vector<int> d(n, INF);
    d[s] = 0;

    bool f = true;
    for (int i = 0; i < n && f; i++) {
        f = false;
        for (auto &x : e) {
            int u = x.u, v = x.v;
            int w = x.w;
            if (d[u] == INF) {
                continue;
            } else if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                f = true;
            }
        }
    }

    assert(f == false);
    return d;
}