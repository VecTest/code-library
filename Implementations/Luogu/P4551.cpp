#include <bits/stdc++.h>

/*
大致思路：
二进制字典树

提交地址：
https://www.luogu.com.cn/problem/P4551
*/

const int S = 0, P = -1;
const int N = 1e5;
const int K = 31;

struct BinaryTrie {
    int a[N * K][2], c;

    BinaryTrie() {
        c = 0;
        memset(a, -1, sizeof(a));
    }

    void insert(int k) {
        int x = 0;
        for (int i = K - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (a[x][b] == -1) {
                a[x][b] = ++c;
            }
            x = a[x][b];
        }
    }

    int get_max(int k) {
        int x = 0, s = 0;
        for (int i = K - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (a[x][b ^ 1] != -1) {
                s += (1 << i);
                x = a[x][b ^ 1];
            } else {
                x = a[x][b];
            }
        }
        return s;
    }

    int get_min(int k) {
        int x = 0, s = 0;
        for (int i = K - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (a[x][b] != -1) {
                x = a[x][b];
            } else {
                s += (1 << i);
                x = a[x][b ^ 1];
            }
        }
        return s;
    }
};

struct Edge {
    int v, w;
};

std::vector<std::vector<Edge>> e;
int d[N];

void dfs(int u, int p, int k) {
    d[u] = k;
    for (int i = 0; i < (int) e[u].size(); i++) {
        int v = e[u][i].v, w = e[u][i].w;
        if (v != p) {
            dfs(v, u, k ^ w);
        }
    }
}

void solve(int n) {
    e = std::vector<std::vector<Edge>>(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    dfs(S, P, 0);

    BinaryTrie bt;
    for (int i = 0; i < n; i++) {
        bt.insert(d[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, bt.get_max(d[i]));
    }
    printf("%d\n", ans);
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        solve(n);
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}