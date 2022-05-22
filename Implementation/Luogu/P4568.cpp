#include <bits/stdc++.h>

/*
大致思路：
分层图最短路

提交地址：
https://www.luogu.com.cn/problem/P4568
https://www.acwing.com/problem/content/2956/
*/

const int INF = 1e9;

struct Edge {
    int v, w;
};
using Graph = std::vector<std::vector<Edge>>;

struct Vertex {
    int d, p;
    bool operator < (const Vertex &x) const {
        return d > x.d;
    }
};

std::vector<int> Dijkstra(int n, int s, Graph &e) {
    std::vector<int> d(n, INF);
    d[s] = 0;

    std::vector<bool> f(n);

    std::priority_queue<Vertex> q;
    q.push({0, s});

    while (!q.empty()) {
        int x = q.top().p;
        q.pop();

        if (f[x]) {
            continue;
        }
        f[x] = true;

        for (int i = 0; i < (int) e[x].size(); i++) {
            int y = e[x][i].v, w = e[x][i].w;
            if (!f[y] && d[y] > d[x] + w) {
                d[y] = d[x] + w;
                q.push({d[y], y});
            }
        }
    }

    return d;
}

void add(int u, int v, int d, Graph &e) {
    e[u].push_back({v, d});
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    int s, t;
    std::cin >> s >> t;

    // 有 k + 1 层，每层有 n 个点，故最大编号为 (k + 1) * n - 1
    int p = (k + 1) * n; // 总点数
    Graph e(p);

    for (int i = 0; i < m; i++) {
        int u, v, d;
        std::cin >> u >> v >> d;
        add(u, v, d, e);
        add(v, u, d, e);

        for (int j = 1; j <= k; j++) { // 建第 j 层的图
            add(u + j * n, v + j * n, d, e);
            add(v + j * n, u + j * n, d, e);

            add(u + (j - 1) * n, v + j * n, 0, e);
            add(v + (j - 1) * n, u + j * n, 0, e);
        }
    }

    std::vector<int> d = Dijkstra(p, s, e);

    int ans = INF;
    for (int i = 0; i <= k; i++) {
        ans = std::min(ans, d[t + i * n]);
    }
    std::cout << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}