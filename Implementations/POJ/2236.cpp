#include <vector>
#include <numeric>
#include <iostream>

/*
大致思路：
并查集 + 欧几里得距离 + 模拟



提交地址：
http://poj.org/problem?id=2236
*/

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
typedef DisjointSetsUnion DSU;

struct P {
    int x, y;
    P() {

    }
    P(int sx, int sy) : x(sx), y(sy) {

    }
};

bool good(P a, P b, int d) {
    int k = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return k <= d * d;
}

int main() {
    std::ios::sync_with_stdio(false);

    int n, d;
    std::cin >> n >> d;

    std::vector<P> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i].x >> p[i].y;
    }

    std::vector<std::vector<bool> > f(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (good(p[i], p[j], d)) {
                f[i][j] = f[j][i] = true;
            }
        }
    }

    std::vector<bool> g(n, false);
    DSU dsu(n);

    char opt;
    while (std::cin >> opt) {
        if (opt == 'O') {
            int x;
            std::cin >> x;
            x--;
            g[x] = true;
            for (int i = 0; i < n; i++) {
                if (!f[x][i] || !g[i] || i == x) {
                    continue;
                }
                dsu.merge(x, i);
            }
        } else if (opt == 'S') {
            int x, y;
            std::cin >> x >> y;
            x--;
            y--;
            std::cout << (dsu.same(x, y) ? "SUCCESS" : "FAIL") << "\n";
        }
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}