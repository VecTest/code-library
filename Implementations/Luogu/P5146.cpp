#include <bits/stdc++.h>

/*
大致思路：
贪心

提交地址：
https://www.luogu.com.cn/problem/P5146
*/

const long long INF = 1e18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    long long ans = -INF;
    long long best = INF;

    for (int i = 0; i < n; i++) {
        ans = std::max(ans, a[i] - best);
        best = std::min(best, a[i]);
    }
    std::cout << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}