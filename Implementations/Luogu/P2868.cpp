#include <bits/stdc++.h>

/*
大致思路：
01 分数规划 + 负环

提交地址：
https://www.luogu.com.cn/problem/P2868
*/

struct Edge {
    int v;
    double w;
};

const double INF = 1e9;

int n, m;
std::vector<int> a;
std::vector<std::vector<Edge>> e;

bool Bellman_Ford(int s, double k) {
    std::vector<double> d(n + 1, INF);
    std::vector<int> c(n + 1);
    std::queue<int> q;
    std::vector<bool> f(n + 1, false);

    d[s] = 0;
    c[s] = 0;
    q.push(s);
    f[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        f[u] = false;

        for (int i = 0; i < (int) e[u].size(); i++) {
            int v = e[u][i].v;
            double w = e[u][i].w * k - a[v];
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                c[v] = c[u] + 1;
                if (c[v] >= n + 1) {
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

bool good(double k) {
    return Bellman_Ford(n, k);
}

int main() {
    scanf("%d%d", &n, &m);
    a = std::vector<int>(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    e = std::vector<std::vector<Edge>>(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        u--;
        v--;
        e[u].push_back({v, w});
    }
    for (int i = 0; i < n; i++) {
        e[n].push_back({i, 0});
    }

    double l = 0, r = 2000;
    for (int i = 0; i < 100; i++) {
        double d = (l + r) / 2;
        if (good(d)) {
            l = d;
        } else {
            r = d;
        }
    }
    printf("%.2lf\n", l);

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}