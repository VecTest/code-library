#include <bits/stdc++.h>

/*
大致思路：
并查集 + 离散化

提交地址：
https://www.luogu.com.cn/problem/P1955
*/

struct DisjointSetsUnion {
    std::vector<int> p, s;
    DisjointSetsUnion() {

    }
    DisjointSetsUnion(int n): p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
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

void discrete(std::vector<int> &a) {
    std::vector<int> b = a;

    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());

    for (auto &x : b) {
        x = std::lower_bound(a.begin(), a.end(), x) - a.begin();
    }
    a = b;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(2 * n), e(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i] >> p[i + n] >> e[i];
    }
    discrete(p);

    DSU dsu(2 * n);
    bool good = true;
    for (int i = 0; i < n; i++) {
        int x = p[i], y = p[i + n];
        if (e[i] == 1) {
            dsu.merge(x, y);
        }
    }
    for (int i = 0; i < n; i++) {
        int x = p[i], y = p[i + n];
        if (e[i] == 0 && dsu.same(x, y)) {
            good = false;
            break;
        }
    }

    std::cout << (good ? "YES" : "NO") << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}