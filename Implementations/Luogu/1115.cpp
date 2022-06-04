#include <bits/stdc++.h>

/*
大致思路：
动态规划
约定 ans 为当前情况下的最优解，best 为以当前下标为**结尾**的非空最长连续子串和

现在考虑转移方程
如果现在处理到了第 i 个元素，best 为以 i - 1 为结尾的非空最长连续子串和
那么，对于 best 来说，它可以取第 i 个元素作为新的结尾，也可以舍弃之前取的所有元素，只取当前的这一个
注意，best 不可以不取当前的元素，因为根据定义，它必须是以当前下标为**结尾**的**非空**最长连续子串和

因为题目要求求出非空最长连续子串和，那么这一个子串一定会有一个**结尾**的地方，所以只需要对于所有的 best 取一个最大值就是答案了

注意：
答案的初始值需要赋值成负无穷，因为非空最长连续子串和有可能是负数

e.g:
input:
2
-1 -2
answer:
-1

提交地址：
https://www.luogu.com.cn/problem/P1115
*/

const int INF = 1e9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int ans = -INF, best = 0; // 注意两个变量的赋值
    for (int i = 0; i < n; i++) {
        best = std::max(a[i], best + a[i]);
        ans = std::max(ans, best);
    }
    std::cout << ans << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}