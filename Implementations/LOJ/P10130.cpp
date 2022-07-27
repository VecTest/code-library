#include <bits/stdc++.h>

/*
大致思路：
倍增 + 最近公共祖先

提交地址：
https://loj.ac/p/10130
*/

const int N = 1e5, LOG = 16;
const int S = 0, P = -1, D = 0;

std::vector<std::vector<int>> e;
int f[N][LOG + 1];
int d[N];

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
    dfs(s, P, D);
    for (int k = 0; k < LOG; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i][k] < 0) {
                f[i][k + 1] = f[i][k];
            } else {
                f[i][k + 1] = f[f[i][k]][k];
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
            u = f[u][k];
            v = f[v][k];
        }
    }
    return f[u][0];
}

int len(int u, int v) {
    return d[u] + d[v] - 2 * d[LCA(u, v)];
}

int main() {
    int n;
    scanf("%d", &n);

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

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        printf("%d\n", len(u, v));
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}