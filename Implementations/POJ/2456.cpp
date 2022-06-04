#include <vector>
#include <iostream>
#include <algorithm>

/*
大致思路：
二分 + 贪心



提交地址：
http://poj.org/problem?id=2456
*/

int n, k;
std::vector<int> a;

bool good(int x) {
    int p = 0;
    for (int i = 1; i < k; i++) {
        int c = p + 1;
        while (c < n && a[c] - a[p] < x) {
            c++;
        }
        if (c == n) {
            return false;
        }
        p = c;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;

    a = std::vector<int>(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    int l = 0, r = 1e9 + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (good(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    std::cout << l << "\n";


#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}