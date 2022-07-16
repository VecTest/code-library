#include <vector>
#include <iostream>

/*
大致思路：
贪心

提交地址：
http://poj.org/problem?id=3617
*/

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<char> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::string ans;
    int l = 0, r = n - 1;

    while (l <= r) {
        bool f = false;

        for (int i = 0; l + i <= r; i++) {
            if (a[l + i] < a[r - i]) {
                f = true;
                break;
            } else if (a[l + i] > a[r - i]) {
                f = false;
                break;
            }
        }

        if (f) {
            ans += a[l++];
        } else {
            ans += a[r--];
        }
    }

    for (int i = 0; i < n; i++) {
        if (i && i % 80 == 0) {
            std::cout << "\n";
        }
        std::cout << ans[i];
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}