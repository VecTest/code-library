#include <bits/stdc++.h>

struct Trie {
    static const int BIT = 31;

    struct Node {
        Node *ch[2] = {nullptr, nullptr};
    };
    Node *root;

    void insert(int k) {
        Node *x = root;
        for (int i = BIT - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (x -> ch[b] == nullptr) {
                x -> ch[b] = new Node;
            }
            x = x -> ch[b];
        }
    }

    int get_max(int k) {
        Node *x = root;
        int ans = 0;
        for (int i = BIT - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (x -> ch[b ^ 1] != nullptr) {
                ans |= (1 << i);
                x = x -> ch[b ^ 1];
            } else {
                x = x -> ch[b];
            }
        }
        return ans;
    }

    int get_min(int k) {
        Node *x = root;
        int ans = 0;
        for (int i = BIT - 1; i >= 0; i--) {
            int b = (k >> i) & 1;
            if (x -> ch[b] != nullptr) {
                x = x -> ch[b];
            } else {
                ans |= (1 << i);
                x = x -> ch[b ^ 1];
            }
        }
        return ans;
    }

    void destroy(Node *x) {
        for (int i = 0; i < 2; i++) {
            if (x -> ch[i] != nullptr) {
                destroy(x -> ch[i]);
            }
        }
        delete(x);
    }

    Trie() {
        root = new Node;
    }

    Trie(std::vector<int> &p) {
        root = new Node;
        for (auto &x : p) {
            insert(x);
        }
    }

    ~Trie() {
        destroy(root);
    }
};