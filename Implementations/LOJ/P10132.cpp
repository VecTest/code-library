#include <bits/stdc++.h>

/*
大致思路：
倍增 + 最近公共祖先 + DFS 时间戳

提交地址：
https://loj.ac/p/10132
*/

const int N = 1e5, LOG = 16;
const int S = 0, P = -1;
const int L = 0;
const int D = 0;

struct Edge {
    int v, w;
};

std::vector<std::vector<Edge>> e;
int f[N][LOG + 1];
int depth[N];
long long dist[N];

int num[N], pos[N], t = 0;

void dfs(int u, int p, int l, long long d) {
    f[u][0] = p;
    depth[u] = l;
    dist[u] = d;

    num[u] = t;
    pos[t++] = u;

    for (int i = 0; i < (int) e[u].size(); i++) {
        int v = e[u][i].v, w = e[u][i].w;
        if (v != p) {
            dfs(v, u, l + 1, d + (long long) w);
        }
    }
}

void process(int n, int s) {
    dfs(s, P, L, D);
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
    if (depth[u] > depth[v]) {
        std::swap(u, v);
    }
    for (int k = LOG; k >= 0; k--) {
        if ((depth[v] - depth[u]) >> k & 1) {
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

long long distance(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[LCA(u, v)];
}

std::set<int> s;
std::set<int>::iterator p;
bool g[N];
long long ans;

void insert(int k) {
    int n = num[k];
    s.insert(n);
    int u = pos[(p = s.lower_bound(n)) == s.begin() ? *--s.end() : *--p];
    int v = pos[(p = s.upper_bound(n)) == s.end() ? *s.begin() : *p];
    long long d = distance(u, k) + distance(k, v) - distance(u, v);
    g[n] = true;
    ans += d;
}

void erase(int k) {
    int n = num[k];
    s.erase(n);
    if (!s.empty()) {
        int u = pos[(p = s.lower_bound(n)) == s.begin() ? *--s.end() : *--p];
        int v = pos[(p = s.upper_bound(n)) == s.end() ? *s.begin() : *p];
        long long d = distance(u, k) + distance(k, v) - distance(u, v);
        g[n] = false;
        ans -= d;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    e = std::vector<std::vector<Edge>>(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    process(n, S);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char o;
        scanf(" %c", &o);
        if (o == '+') {
            int k;
            scanf("%d", &k);
            k--;
            insert(k);
        } else if (o == '-') {
            int k;
            scanf("%d", &k);
            k--;
            erase(k);
        } else {
            printf("%lld\n", ans / 2);
        }
    }

    return 0;
}