#include <cstdio>
#include <vector>
#include <cassert>

/*
大致思路：
矩阵加速

提交地址：
http://acm.hdu.edu.cn/showproblem.php?pid=5015
*/

const int MOD = 1e7 + 7;

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

template <typename S, typename T>
Matrix<T> power(Matrix<T> A, S b) {
    Matrix<T> R(A.n, A.n);
    R.identity();

    while (b) {
        if (b & 1) {
            R *= A;
        }
        A *= A;
        b /= 2;
    }

    return R;
}

void solve(int n, int m) {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    Matrix<long long> A(n + 2, 1);
    A.a[0][0] = 23;
    for (int i = 1; i < n + 1; i++) {
        A.a[i][0] = a[i - 1];
    }
    A.a[n + 1][0] = 1;

    Matrix<long long> B(n + 2, n + 2);
    for (int i = 0; i < n + 1; i++) {
        B.a[i][0] = 10;
        B.a[i][n + 1] = 3;
    }
    B.a[n + 1][n + 1] = 1;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j <= i; j++) {
            B.a[i][j] = 1;
        }
    }

    Matrix<long long> R = power(B, m) * A;
    printf("%lld\n", R.a[n][0]);
}

int main() {
    int n, m;

    while (~scanf("%d%d", &n, &m)) {
        solve(n, m);
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}