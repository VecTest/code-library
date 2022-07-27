#include <bits/stdc++.h>

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion(int n): p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
    }
    DisjointSetsUnion() {

    }
    int get(int x) {
        return p[x] = (x == p[x] ? x : get(p[x]));
    }
    bool same(int x, int y) {
        return get(x) == get(y);
    }
    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
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
        return s[get(x)];
    }
};
using DSU = DisjointSetsUnion;