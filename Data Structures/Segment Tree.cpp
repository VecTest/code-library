#include <bits/stdc++.h>

struct Node {
    int sum;

    void apply(int t) {
        sum = t;
    }

    void update(int t) {
        sum += t;
    }
};

struct SegmentTree {
    int n;
    std::vector<Node> a;

    const Node NEUTRAL_ELEMENT = {0};

    Node merge(Node x, Node y) {
        return {
            x.sum + y.sum
        };
    }

    void pull(int x) {
        a[x] = merge(a[x * 2 + 1], a[x * 2 + 2]);
    }

    void push(int x, int lx, int rx) {

    }

    void build(int x, int lx, int rx, std::vector<int> &p) {
        if (rx - lx == 1) {
            a[x].apply(p[lx]);
        } else {
            int m = (lx + rx) / 2;
            build(x * 2 + 1, lx, m, p);
            build(x * 2 + 2, m, rx, p);
            pull(x);
        }
    }

    void modify(int x, int lx, int rx, int p, int t) {
        if (rx - lx == 1) {
            a[x].update(t);
        } else {
            push(x, lx, rx);
            int m = (lx + rx) / 2;
            if (p < m) {
                modify(x * 2 + 1, lx, m, p, t);
            } else if (p >= m) {
                modify(x * 2 + 2, m, rx, p, t);
            }
            pull(x);
        }
    }

    void modify(int p, int t) {
        modify(0, 0, n, p, t);
    }

    Node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return a[x];
        } else if (rx <= l || r <= lx) {
            return NEUTRAL_ELEMENT;
        } else {
            push(x, lx, rx);
            int m = (lx + rx) / 2;
            Node p = query(x * 2 + 1, lx, m, l, r);
            Node q = query(x * 2 + 2, m, rx, l, r);
            return merge(p, q);
        }
    }

    Node query(int l, int r) {
        return query(0, 0, n, l, r);
    }

    SegmentTree() {

    }

    SegmentTree(int s) {
        n = s;
        a = std::vector<Node>(n * 4);
        std::vector<int> t(n);
        build(0, 0, n, t);
    }

    SegmentTree(std::vector<int> &p) {
        n = (int) p.size();
        a = std::vector<Node>(n * 4);
        build(0, 0, n, p);
    }
};