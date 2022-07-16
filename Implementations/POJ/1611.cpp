#include <vector>
#include <numeric>
#include <iostream>

/*
大致思路：
并查集

提交地址：
http://poj.org/problem?id=1611
*/

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion(int n): p(n), s(n, 1) {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
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
typedef DisjointSetsUnion DSU;

int n, m;

void solve() {
    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int k;
        std::cin >> k;
        std::vector<int> g(k);
        for (int j = 0; j < k; j++) {
            std::cin >> g[j];
        }
        for (int j = 1; j < k; j++) {
            dsu.merge(g.front(), g[j]);
        }
    }

    int p = dsu.find(0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (int) (dsu.same(p, dsu.find(i)));
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);

    while (std::cin >> n >> m && (n || m)) {
        solve();
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}