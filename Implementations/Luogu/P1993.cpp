#include <bits/stdc++.h>

/*
大致思路：
差分约束

提交地址：
https://www.luogu.com.cn/problem/P1993
*/

const int INF = 1e9;

struct Edge {
    int v, w;
};

bool Bellman_Ford(int n, int s, std::vector<std::vector<Edge>> &e) {
    std::vector<int> d(n, INF), c(n);
    std::queue<int> q;
    std::vector<bool> f(n, false);

    d[s] = 0;
    c[s] = 0;
    q.push(s);
    f[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        f[u] = false;

        for (int i = 0; i < (int) e[u].size(); i++) {
            int v = e[u][i].v, w = e[u][i].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                c[v] = c[u] + 1;
                if (c[v] >= n) {
                    return true;
                }
                if (!f[v]) {
                    q.push(v);
                    f[v] = true;
                }
            }
        }
    }

    return false;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    std::vector<std::vector<Edge>> e(n + 1);
    for (int i = 0; i < m; i++) {
        int o, u, v;
        scanf("%d%d%d", &o, &u, &v);
        u--;
        v--;
        if (o == 1) {
            int w;
            scanf("%d", &w);
            e[u].push_back({v, -w});
        } else if (o == 2) {
            int w;
            scanf("%d", &w);
            e[v].push_back({u, w});
        } else if (o == 3) {
            e[u].push_back({v, 0});
            e[v].push_back({u, 0});
        }
    }
    for (int i = 0; i < n; i++) {
        e[n].push_back({i, 0});
    }

    bool f = Bellman_Ford(n + 1, n, e);
    puts(f ? "No" : "Yes");

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}