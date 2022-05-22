#include <bits/stdc++.h>

/*
大致思路：
拆点 + 二分图最大匹配
把棋盘拆成国际象棋棋盘（黑白交替），显然一块骨牌必须覆盖一个黑块，一个白块
拆点后，只需要跑两个集合（黑点和白点）的二分图最大匹配即可

跑二分图最大匹配需要的性质：
1. 节点能分成独立的两个集合，每个集合內部有 0 条边
    满足，因为一块骨牌不可以斜着放
2. 每个节点只能与 1 条匹配边相连
    显然满足

提交地址：
https://www.acwing.com/problem/content/374/
*/

const int N = 100;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

int n, m;
bool g[N][N];

bool v[N][N];
std::pair<int, int> p[N][N];

bool match(std::pair<int, int> x) {
    for (int i = 0; i < 4; i++) {
        int a = x.first + dx[i];
        int b = x.second + dy[i];

        if (a < 0 || a >= n || b < 0 || b >= n || v[a][b] || !g[a][b]) {
            continue;
        }
        v[a][b] = true;

        if (p[a][b] == std::make_pair(-1, -1) || match(p[a][b])) {
            p[a][b] = x;
            return true;
        }
    }

    return false;
}

int Hungarian() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = {-1, -1};
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2 == 1 || !g[i][j]) {
                continue;
            }
            memset(v, false, sizeof(v));
            ans += (int) match({i, j});
        }
    }

    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    memset(g, true, sizeof(g));
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        g[x][y] = false;
    }

    std::cout << Hungarian() << "\n";

#ifdef LOCAL
    std::cout << std::flush;
    system("pause");
#endif
    return 0;
}