#include <iostream>

/*
大致思路：
博弈论



提交地址：
http://poj.org/problem?id=2484
*/

int main() {
    std::ios::sync_with_stdio(false);

    int n;

    while (std::cin >> n && n) {
        if (n <= 2) {
            std::cout << "Alice" << "\n";
        } else {
            std::cout << "Bob" << "\n";
        }
    }

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}