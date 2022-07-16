#include <cmath>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <iostream>

/*
大致思路：
二分

提交地址：
http://poj.org/problem?id=1064
*/

int n, k;
std::vector<long double> a;

bool good(long double x) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += (int) (a[i] / x);
    }
    return s >= k;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;

    a = std::vector<long double>(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    long double l = 0, r = 2e9;
    for (int i = 0; i < 100; i++) {
        long double m = (l + r) / 2;
        if (good(m)) {
            l = m;
        } else {
            r = m;
        }
    }

    long double ans = floor(l * 100) / 100;
    std::cout << std::fixed << std::setprecision(2) << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}