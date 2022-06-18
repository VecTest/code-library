#include <bits/stdc++.h>

// Record: https://judge.yosupo.jp/submission/92515

struct SparseTable {
    int n;
    std::vector<int> LOG;
    std::vector<std::vector<int>> f; // f[i][j] : [l, l + 2 ^ j)
    SparseTable() {

    }
    SparseTable(std::vector<int> &a) {
        n = (int) a.size();

        LOG = std::vector<int>(n + 1);
        LOG[1] = 0;
        for (int i = 2; i <= n; i++) {
            LOG[i] = LOG[i / 2] + 1;
        }

        int K = LOG[n];
        f = std::vector<std::vector<int>>(n, std::vector<int>(K + 1));
        for (int i = 0; i < n; i++) {
            f[i][0] = a[i];
        }

        for (int k = 1; k <= K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                f[i][k] = std::max(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) {
        int K = LOG[r - l];
        int ans = std::max(f[l][K], f[r - (1 << K)][K]);
        return ans;
    }
};
using ST = SparseTable;