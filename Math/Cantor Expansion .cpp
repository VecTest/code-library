#include <bits/stdc++.h>

struct Cantor {
    static const int MOD = 998244353;

    int n;
    std::vector<int> f;

    Cantor() {

    }

    Cantor(int s) {
        assert(s > 0);
        n = s;
        f = std::vector<int>(n);
        f[0] = 1;
        for (int i = 1; i < n; i++) {
            f[i] = f[i - 1] * i % MOD;
        }
    }

    int rank(std::vector<int> a) {
        assert(n == (int) a.size());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = i + 1; j < n; j++) {
                s += (int) (a[j] < a[i]);
            }
            ans = (ans + s * f[n - 1 - i] % MOD) % MOD;
        }
        return ans + 1;
    }
};

// struct Cantor {
//     int n;
//     std::vector<int> f;

//     Cantor() {

//     }

//     Cantor(int s) {
//         assert(s > 0);
//         n = s;
//         f = std::vector<int>(n);
//         f[0] = 1;
//         for (int i = 1; i < n; i++) {
//             f[i] = f[i - 1] * i;
//         }
//     }

//     int rank(std::vector<int> a) {
//         assert(n == (int) a.size());
//         int ans = 0;
//         for (int i = 0; i < n; i++) {
//             int s = 0;
//             for (int j = i + 1; j < n; j++) {
//                 s += (int) (a[j] < a[i]);
//             }
//             ans = (ans + s * f[n - 1 - i]);
//         }
//         return ans + 1;
//     }
// };