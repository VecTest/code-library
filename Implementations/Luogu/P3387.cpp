#include <bits/stdc++.h>

/*
大致思路：
缩点 + 拓扑排序 + 动态规划

提交地址：
https://www.luogu.com.cn/problem/P3387
*/

const int N = 1e4;
const int INF = 1e9;

int n, m;
int w[N];
std::vector<std::vector<int>> e0, e1;

int f[N], l[N], t;
std::stack<int> s;
bool g[N];
int SCC[N];

void dfs(int u) {
    f[u] = l[u] = t++;
    s.push(u);
    g[u] = true;

    for (int i = 0; i < (int) e0[u].size(); i++) {
        int v = e0[u][i];
        if (f[v] == -1) {
            dfs(v);
            l[u] = std::min(l[u], l[v]);
        } else if (g[v]) {
            l[u] = std::min(l[u], l[v]);
        }
    }

    if (f[u] == l[u]) {
        int v;
        while (true) {
            v = s.top();
            s.pop();
            g[v] = false;
            SCC[v] = u;
            if (u == v) {
                break;
            }
            w[u] += w[v];
        }
    }
}

void Tarjan() {
    t = 0;
    std::fill(f, f + n, -1);
    for (int i = 0; i < n; i++) {
        if (f[i] == -1) {
            dfs(i);
        }
    }
}

int indegree[N];

int topological_sort() {
    std::queue<int> q;
    int d[N];

    std::fill(d, d + n, -INF);
    for (int i = 0; i < n; i++) {
        if (SCC[i] == i && indegree[i] == 0) {
            q.push(i);
            d[i] = w[i];
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int) e1[u].size(); i++) {
            int v = e1[u][i];
            indegree[v]--;
            d[v] = std::max(d[v], d[u] + w[v]);
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return *std::max_element(d, d + n);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    e0 = e1 = std::vector<std::vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        e0[u].push_back(v);
    }

    Tarjan();

    for (int u = 0; u < n; u++) {
        for (int i = 0; i < (int) e0[u].size(); i++) {
            int v = e0[u][i];
            if (SCC[u] != SCC[v]) {
                e1[SCC[u]].push_back(SCC[v]);
                indegree[SCC[v]]++;
            }
        }
    }
    printf("%d\n", topological_sort());

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}