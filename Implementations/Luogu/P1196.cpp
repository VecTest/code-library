#include <bits/stdc++.h>

/*
大致思路：
带权并查集

提交地址：
https://www.luogu.com.cn/problem/P1196
https://loj.ac/p/2294
*/

const int N = 3e4;

struct DisjointSetsUnion {
    int p[N], s[N];
    int d[N];

    DisjointSetsUnion() {
        for (int i = 0; i < N; i++) {
            p[i] = i;
            s[i] = 1;
            d[i] = 0;
        }
    }

    int find(int x) {
        if (x == p[x]) {
            return x;
        } else {
            int r = find(p[x]);
            d[x] += d[p[x]];
            return p[x] = r;
        }
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        } else {
            p[x] = y;
            d[x] = s[y];
            s[y] += s[x];
            s[x] = 0;
            return true;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int query(int x, int y) {
        if (same(x, y)) {
            return std::max(std::abs(d[x] - d[y]) - 1, 0);
        } else {
            return -1;
        }
    }
};
using DSU = DisjointSetsUnion;

int main() {
    int n;
    scanf("%d", &n);

    DSU dsu;
    for (int i = 0; i < n; i++) {
        char opt;
        int x, y;
        scanf(" %c%d%d", &opt, &x, &y);
        x--;
        y--;
        if (opt == 'M') {
            dsu.merge(x, y);
        } else if (opt == 'C') {
            printf("%d\n", dsu.query(x, y));
        }
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}