#include <vector>
#include <iostream>
#include <algorithm>

/*
大致思路：
折半枚举（双向搜索）

提交地址：
http://poj.org/problem?id=2785
*/

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    std::vector<int> f(n * n), g(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f[i * n + j] = a[i] + b[j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i * n + j] = c[i] + d[j];
        }
    }
    std::sort(g.begin(), g.end());

    long long ans = 0;
    for (int i = 0; i < n * n; i++) {
        std::vector<int>::iterator x = std::lower_bound(g.begin(), g.end(), -f[i]);
        std::vector<int>::iterator y = std::upper_bound(g.begin(), g.end(), -f[i]);
        ans += (long long) (y - x);
    }
    std::cout << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}