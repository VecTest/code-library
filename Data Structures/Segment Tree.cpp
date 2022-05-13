#include <bits/stdc++.h>

struct Node {
    int key;
    int prefix, suffix, sum;

    void apply(int x) {
        key = prefix = suffix = x;
        sum = x;
    }
};

struct SegmentTree {
    static const int INF = 1e9;

    int n;
    std::vector<Node> a;
    Node NEUTRAL_ELEMENT = {-INF, -INF, -INF, -INF};

    Node merge(Node &x, Node &y) {
        return {
            std::max({x.key, y.key, x.suffix + y.prefix}),
            std::max(x.prefix, x.sum + y.prefix),
            std::max(y.suffix, y.sum + x.suffix),
            x.sum + y.sum
        };
    }

    void pull(int x) {
        a[x] = merge(a[x * 2 + 1], a[x * 2 + 2]);
    }

    void push(int x) {

    }

    void build(int x, int lx, int rx, std::vector<int> &p) {
        if (lx == rx) {
            a[x].apply(p[lx]);
            return;
        }
        int m = (lx + rx) >> 1;
        build(x * 2 + 1, lx, m, p);
        build(x * 2 + 2, m + 1, rx, p);
        pull(x);
    }

    Node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return a[x];
        }
        if (rx < l || r < lx) {
            return NEUTRAL_ELEMENT;
        }
        push(x);
        int m = (lx + rx) >> 1;
        Node p = query(x * 2 + 1, lx, m, l, r), q = query(x * 2 + 2, m + 1, rx, l, r);
        return merge(p, q);
    }

    Node query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void modify(int x, int lx, int rx, int p, int k) {
        if (lx == rx) {
            a[x].apply(k);
            return;
        }
        push(x);
        int m = (lx + rx) >> 1;
        if (p <= m) {
            modify(x * 2 + 1, lx, m, p, k);
        } else if (m < p) {
            modify(x * 2 + 2, m + 1, rx, p, k);
        }
        pull(x);
    }

    void modify(int p, int k) {
        modify(0, 0, n - 1, p, k);
    }

    SegmentTree() {

    }

    SegmentTree(std::vector<int> &p) {
        n = (int) p.size();
        assert(n > 0);
        a.resize(n << 2);
        build(0, 0, n - 1, p);
    }
};