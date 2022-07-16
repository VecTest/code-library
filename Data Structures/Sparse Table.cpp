#include <bits/stdc++.h>

// Record: https://judge.yosupo.jp/submission/95105

const int N = 5e5, LOG = 18;

struct SparseTable {
    int f[N][LOG + 1];
    int L[N + 1];

    SparseTable() {

    }

    SparseTable(int n, int *a) {
        for (int i = 0; i < n; i++) {
            f[i][0] = a[i];
        }

        L[1] = 0;
        for (int i = 2; i <= n; i++) {
            L[i] = L[i / 2] + 1;
        }

        int K = L[n];
        for (int k = 1; k <= K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                f[i][k] = std::min(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int query(int l, int r) {
        int K = L[r - l];
        return std::min(f[l][K], f[r - (1 << K)][K]);
    }
};
using ST = SparseTable;