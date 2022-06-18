#include <bits/stdc++.h>

/*
大致思路：
扩展欧几里得算法

提交地址：
https://www.luogu.com.cn/problem/P1082
*/

template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    T d;
    if (b == 0) {
        d = a;
        x = 1, y = 0;
    } else {
        d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    return d;
}

int main() {
    long long a, b, x, y;
    scanf("%lld %lld", &a, &b);

    exgcd(a, b, x, y);
    x = (x % b + b) % b;
    printf("%lld\n", x);

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}