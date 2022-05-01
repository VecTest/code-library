#include <bits/stdc++.h>

struct Trie {
    static const int K = 31;

    struct Node {
        Node *c[2];

        Node() {
            c[0] = c[1] = nullptr;
        }
    };
    Node *s;

    void insert(int key) {
        Node *x = s;
        for (int i = K - 1; i >= 0; i--) {
            int b = (key >> i) & 1;
            if (x -> c[b] == nullptr) {
                x -> c[b] = new Node;
            }
            x = x -> c[b];
        }
    }

    int get_max(int key) {
        Node *x = s;
        int answer = 0;

        for (int i = K - 1; i >= 0; i--) {
            int b = (key >> i) & 1;
            if (x -> c[b ^ 1] != nullptr) {
                answer |= (1 << i);
                x = x -> c[b ^ 1];
            } else {
                x = x -> c[b];
            }
        }

        return answer;
    }

    int get_min(int key) {
        Node *x = s;
        int answer = 0;

        for (int i = K - 1; i >= 0; i--) {
            int b = (key >> i) & 1;
            if (x -> c[b] != nullptr) {
                x = x -> c[b];
            } else {
                answer |= (1 << i);
                x = x -> c[b ^ 1];
            }
        }

        return answer;
    }

    void destroy(Node *x) {
        for (int i = 0; i < 2; i++) {
            if (x -> c[i] != nullptr) {
                destroy(x -> c[i]);
            }
        }
        delete(x);
    }

    Trie() {
        s = new Node;
    }

    Trie(std::vector<int> &p) {
        s = new Node;
        for (int i = 0; i < (int) p.size(); i++) {
            insert(p[i]);
        }
    }

    ~Trie() {
        destroy(s);
    }
};

void solve() {
    int l, r;
    std::cin >> l >> r;

    int n = r - l + 1;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    Trie tr(a);
    for (int i = 0; i < n; i++) {
        int x = a[i] ^ l;
        if (tr.get_min(x) == l && tr.get_max(x) == r) {
            std::cout << x << "\n";
            return;
        }
    }
}