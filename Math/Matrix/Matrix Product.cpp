#include <bits/stdc++.h>

// Record: https://judge.yosupo.jp/submission/92941

const int MOD = 998244353;

template <typename T>
struct Matrix {
    int n, m;
    std::vector<std::vector<T>> a;
    Matrix() {

    }
    Matrix(int r, int c) {
        n = r, m = c;
        a = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
    }
    void identity() {
        assert(n == m);
        for (int i = 0; i < n; i++) {
            a[i][i] = 1;
        }
    }
    friend Matrix operator * (const Matrix &A, const Matrix &B) {
        assert(A.m == B.n);
        Matrix R(A.n, B.m);
        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < B.m; j++) {
                for (int k = 0; k < A.m; k++) {
                    R.a[i][j] = (R.a[i][j] + A.a[i][k] * B.a[k][j] % MOD) % MOD;
                }
            }
        }
        return R;
    }
    Matrix operator *= (const Matrix &A) {
        return *this = *this * A;
    }
};