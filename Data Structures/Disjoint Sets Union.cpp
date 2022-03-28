#include <bits/stdc++.h>

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion(int n) : p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
        return;
    }
    void resize(int n) {
        p.resize(n);
        s.assign(n, 1);
        std::iota(p.begin(), p.end(), 0);
        return;
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