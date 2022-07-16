#include <vector>
#include <cstdio>

/*
大致思路：
种类并查集

提交地址：
http://poj.org/problem?id=1703
*/

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion() {

    }
    DisjointSetsUnion(int n): p(n), s(n, 1) {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
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
typedef DisjointSetsUnion DSU;

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);

    DSU dsu(2 * n);

    for (int i = 0; i < m; i++) {
        char opt;
        int x, y;
        scanf(" %c%d%d", &opt, &x, &y);
        x--;
        y--;
        if (opt == 'A') {
            if (dsu.same(x, y)) {
                puts("In the same gang.");
            } else if (dsu.same(x, y + n)) {
                puts("In different gangs.");
            } else {
                puts("Not sure yet.");
            }
        } else {
            dsu.merge(x, y + n);
            dsu.merge(x + n, y);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}