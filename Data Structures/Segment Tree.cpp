#include <bits/stdc++.h>

struct SegmentTree {
    struct Node {
        long long key, tag;
    };

    int n;
    std::vector<Node> a;

    void set(int x, int d) {
        a[x].key = d;
        a[x].tag = 0;
    }

    void pull(int x) {
        a[x].key = a[x * 2 + 1].key + a[x * 2 + 2].key;
    }

    void push(int x, int lx, int rx) {
        if (a[x].tag != 0 && lx != rx) {
            int m = (lx + rx) >> 1;

            a[x * 2 + 1].tag += a[x].tag;
            a[x * 2 + 1].key += (m - lx + 1) * a[x].tag;

            a[x * 2 + 2].tag += a[x].tag;
            a[x * 2 + 2].key += (rx - m) * a[x].tag;

            a[x].tag = 0;
        }
    }

    void build(std::vector<int> &p, int x, int lx, int rx) {
        if (lx == rx) {
            set(x, p[lx]);
            return;
        }
        int m = (lx + rx) >> 1;
        build(p, x * 2 + 1, lx, m);
        build(p, x * 2 + 2, m + 1, rx);
        pull(x);
    }

    void build(std::vector<int> &p) {
        n = (int) p.size();
        a.resize(n << 2);
        build(p, 0, 0, n - 1);
    }

    SegmentTree(std::vector<int> &p) {
        build(p);
    }

    long long query(int l, int r, int x, int lx, int rx) {
        if (l <= lx && rx <= r) {
            return a[x].key;
        } else if (rx < l || r < lx) {
            return 0;
        }
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        long long ls = query(l, r, x * 2 + 1, lx, m);
        long long rs = query(l, r, x * 2 + 2, m + 1, rx);
        return ls + rs;
    }

    long long query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }

    void modify(int l, int r, int d, int x, int lx, int rx) {
        if (l <= lx && rx <= r) {
            a[x].key += (rx - lx + 1) * (long long) d;
            a[x].tag += d;
            return;
        } else if (rx < l || r < lx) {
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        if (l <= m) {
            modify(l, r, d, x * 2 + 1, lx, m);
        }
        if (m + 1 <= r) {
            modify(l, r, d, x * 2 + 2, m + 1, rx);
        }
        pull(x);
    }

    void modify(int l, int r, int d) {
        modify(l, r, d, 0, 0, n - 1);
    }

    void test() {
        std::cout << "test:\n";
        std::cout << a[0].key << "\n";
        std::cout << a[1].key << "\n";
        std::cout << a[2].key << "\n";
        std::cout << "\n";
    }
};
using ST = SegmentTree;