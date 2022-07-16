#include <bits/stdc++.h>

std::vector<int> Euler(int n) {
    std::vector<int> p;

    std::vector<bool> f(n + 1, true);
    f[0] = f[1] = false;

    for (int i = 2; i <= n; i++) {
        if (f[i]) {
            p.push_back(i);
        }
        for (int j = 0; j < (int) p.size() && i * p[j] <= n; j++) {
            f[i * p[j]] = false;
            if (i % p[j] == 0) {
                break;
            }
        }
    }

    return p;
}