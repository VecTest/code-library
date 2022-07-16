#include <bits/stdc++.h>

/*
大致思路：
最近公共祖先

提交地址：
https://www.luogu.com.cn/problem/P3398
*/

const int N = 5e5, LOG = 18;
const int S = 0, P = -1;

int f[N][LOG + 1], d[N];
std::vector<std::vector<int>> e;

void dfs(int u, int p, int k) {
    f[u][0] = p;
    d[u] = k;
    for (int i = 0; i < (int) e[u].size(); i++) {
        int v = e[u][i];
        if (v != p) {
            dfs(v, u, k + 1);
        }
    }
}

void process(int n, int s) {
    dfs(s, P, 0);
    for (int k = 1; k <= LOG; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i][k - 1] < 0) {
                f[i][k] = f[i][k - 1];
            } else {
                f[i][k] = f[f[i][k - 1]][k - 1];
            }
        }
    }
}

int LCA(int u, int v) {
    if (d[u] > d[v]) {
        std::swap(u, v);
    }
    for (int k = LOG; k >= 0; k--) {
        if ((d[v] - d[u]) >> k & 1) {
            v = f[v][k];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = LOG; k >= 0; k--) {
        if (f[u][k] != f[v][k]) {
            u = f[u][k], v = f[v][k];
        }
    }
    return f[u][0];
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[LCA(u, v)];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    e = std::vector<std::vector<int>>(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    process(n, S);

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a--;
        b--;
        c--;
        d--;
        int u = LCA(a, b);
        int v = LCA(c, d);
        if (dist(c, u) + dist(u, d) == dist(c, d) || dist(a, v) + dist(v, b) == dist(a, b)) {
            puts("Y");
        } else {
            puts("N");
        }
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}