#include <bits/stdc++.h>

/*
大致思路：
01 背包

提交地址：
https://www.luogu.com.cn/problem/T241268
*/

const int N = 400;
const int V = 100;
const int INF = 1e9;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int w[N], v[N];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }

    int f[N * V + 1];
    // f[i + 1][j] 表示前 i 个物品中挑选出价值总和为 j 时总重量的最小值

    std::fill(f, f + N * V + 1, INF);
    f[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = N * V; j >= 0; j--) {
            if (j < v[i]) {
                f[j] = f[j];
            } else {
                f[j] = std::min(f[j], f[j - v[i]] + w[i]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= N * V; i++) {
        if (f[i] <= m) {
            ans = i;
        }
    }
    printf("%d\n", ans);

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}