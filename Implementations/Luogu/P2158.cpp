#include <bits/stdc++.h>

/*
大致思路：
欧拉函数

提交地址：
https://www.luogu.com.cn/problem/P2158
*/

std::vector<int> Euler(int n) {
    std::vector<int> p;

    std::vector<bool> f(n + 1, true);
    f[0] = f[1] = false;

    std::vector<int> phi(n + 1);
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (f[i]) {
            p.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < (int) p.size() && i * p[j] <= n; j++) {
            f[i * p[j]] = false;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }

    return phi;
}

int main() {
    int n;
    scanf("%d", &n);

    if (n == 1) {
        printf("0\n");
    } else {
        std::vector<int> phi = Euler(n);
        int ans = 0;
        for (int i = 1; i <= n - 1; i++) {
            ans += phi[i];
        }
        printf("%d\n", ans * 2 + 1);
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}