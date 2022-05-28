#include <bits/stdc++.h>

struct Node {
    int sum;

    void apply(int x) {
        sum = x;
    }
};

struct SegmentTree {
    int n;
    std::vector<Node> a;

    Node NEUTRAL_ELEMENT = {0};

    Node merge(Node x, Node y) {
        return {
            x.sum + y.sum
        };
    }

    void pull(int x) {
        a[x] = merge(a[x * 2 + 1], a[x * 2 + 2]);
    }

    void push(int x) {

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

    Node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return a[x];
        } else if (rx <= l || r <= lx) {
            return NEUTRAL_ELEMENT;
        } else {
            push(x);
            int m = (lx + rx) / 2;
            Node p = query(x * 2 + 1, lx, m, l, r), q = query(x * 2 + 2, m, rx, l, r);
            return merge(p, q);
        }
    }

    Node query(int l, int r) {
        return query(0, 0, n, l, r);
    }

    void modify(int x, int lx, int rx, int p, int k) {
        if (rx - lx == 1) {
            // a[x].apply(k);
            a[x].sum += k;
        } else {
            push(x);
            int m = (lx + rx) / 2;
            if (p < m) {
                modify(x * 2 + 1, lx, m, p, k);
            } else {
                modify(x * 2 + 2, m, rx, p, k);
            }
            pull(x);
        }
    }

    void modify(int p, int k) {
        modify(0, 0, n, p, k);
    }

    SegmentTree() {

    }

    SegmentTree(std::vector<int> &p) {
        assert(p.size() > 0);
        for (n = 1; n < (int) p.size(); ) {
            n *= 2;
        }
        a = std::vector<Node>(n * 2);
        build(0, 0, n, p);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    SegmentTree st(a);

    for (int i = 0; i < m; i++) {
        int opt;
        std::cin >> opt;

        if (opt == 1) {
            int p, k;
            std::cin >> p >> k;
            p--;
            st.modify(p, k);
        } else if (opt == 2) {
            int l, r;
            std::cin >> l >> r;
            l--;
            std::cout << st.query(l, r).sum << "\n";
        }
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}