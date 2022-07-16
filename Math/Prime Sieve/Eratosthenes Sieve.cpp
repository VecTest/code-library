#include <bits/stdc++.h>

std::vector<int> Eratosthenes(int n) {
    std::vector<int> p;

    std::vector<bool> f(n + 1, true);
    f[0] = f[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (f[i]) {
            for (int j = i * i; j <= n; j += i) {
                f[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (f[i]) {
            p.push_back(i);
        }
    }

    return p;
}