#include <vector>
#include <iostream>

/*
大致思路：
动态规划

提交地址：
http://poj.org/problem?id=3176
*/

const int INF = 1e9;

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector<std::vector<int>> f(n, std::vector<int>(n, -INF));
    f[0][0] = a[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            f[i][j] = std::max(f[i][j], f[i - 1][j] + a[i][j]);
            if (j) {
                f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + a[i][j]);
            }
        }
    }

    int ans = -INF;
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, f[n - 1][i]);
    }
    std::cout << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}