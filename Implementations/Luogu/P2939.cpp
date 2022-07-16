#include <bits/stdc++.h>

/*
大致思路：
分层图最短路

提交地址：
https://www.luogu.com.cn/problem/P2939
*/

const int INF = 1e9;
const int S = 0;

struct Edge {
    int v, w;
};

struct Node {
    int p, d;
    bool operator < (const Node &x) const {
        return d > x.d;
    }
};

std::vector<int> Dijkstra(int n, int s, std::vector<std::vector<Edge>> &e) {
    std::vector<int> d(n, INF);
    d[s] = 0;

    std::vector<bool> f(n, false);

    std::priority_queue<Node> q;
    q.push({s, 0});

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
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    std::vector<std::vector<Edge>> e(n * (k + 1));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        for (int j = 0; j <= k; j++) {
            e[u + j * n].push_back({v + j * n, w});
            e[v + j * n].push_back({u + j * n, w});
        }
        for (int j = 0; j < k; j++) {
            e[u + j * n].push_back({v + (j + 1) * n, 0});
            e[v + j * n].push_back({u + (j + 1) * n, 0});
        }
    }

    std::vector<int> d = Dijkstra(n * (k + 1), S, e);
    int ans = INF;
    for (int i = 0; i <= k; i++) {
        ans = std::min(ans, d[(n - 1) + i * n]);
    }
    printf("%d\n", ans);

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}