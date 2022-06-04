#include <vector>
#include <numeric>
#include <iostream>

/*
大致思路：
带权并查集



提交地址：
http://acm.hdu.edu.cn/showproblem.php?pid=3038
*/

struct DisjointSetsUnion {
    std::vector<int> p, k;
    DisjointSetsUnion(int n) : p(n), k(n, 0) {
        std::iota(p.begin(), p.end(), 0);
    }
    DisjointSetsUnion() {

    }
    int find(int x) {
        if (x == p[x]) {
            return x;
        } else {
            int t = p[x];
            p[x] = find(p[x]);
            k[x] += k[t];
            return p[x];
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void merge(int x, int y, int w) {
        int xr = find(x);
        int yr = find(y);
        if (xr != yr) {
            p[xr] = yr;
            k[xr] = k[y] + w - k[x];
        }
    }
};
using DSU = DisjointSetsUnion;

int n, m;

void solve() {
    DSU dsu(n + 1);
    int ans = 0;

    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        x--;

        if (!dsu.same(x, y)) {
            dsu.merge(x, y, w);
        } else {
            ans += (int) (dsu.k[x] - dsu.k[y] != w);
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m) {
        solve();
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}