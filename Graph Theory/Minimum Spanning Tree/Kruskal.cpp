#include <bits/stdc++.h>

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion(int n) : p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
    }
    DisjointSetsUnion() {

    }
    int find(int x) {
        return p[x] = (x == p[x] ? x : find(p[x]));
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (s[x] > s[y]) {
            std::swap(x, y);
        }
        s[y] += s[x];
        p[x] = y;
        return true;
    }
    int size(int x) {
        return s[find(x)];
    }
};
using DSU = DisjointSetsUnion;

struct Edge {
    int u, v, w;

    bool operator < (const Edge &x) const {
        return w < x.w;
    }
};

int Kruskal(int n, int m, std::vector<Edge> &e) {
    std::sort(e.begin(), e.end());

    DSU dsu(n);
    int ans = 0, c = 0;
    for (int i = 0; i < m; i++) {
        int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
        if (!dsu.same(u, v)) {
            ans += e[i].w;
            dsu.merge(u, v);
            if (++c == n - 1) {
                break;
            }
        }
    }

    assert(c == n - 1);
    return ans;
}