#include <bits/stdc++.h>

/*
大致思路：
种类并查集
用两个并查集，一个表示朋友关系，一个表示敌人关系
通过表示敌人关系的并查集实现 “敌人的敌人时朋友”

易错点：
约定 ~A 表示 A 的敌人的代表
1. 如果 A 与 B 是敌人关系，~A - B，A - ~B 两条边都需要连接
2. 如果 A 与 B 是朋友关系，只需要连接 A - B，不能连接 ~A - ~B（否则无法保证答案最大）
3. 敌人关系的连边应该让敌人的代表连向朋友的代表，而不是反过来（方便统计答案）

跑二分图最大匹配需要的性质：
1. 节点能分成独立的两个集合，每个集合內部有 0 条边
    满足，因为一块骨牌不可以斜着放
2. 每个节点只能与 1 条匹配边相连
    显然满足

提交地址：
https://www.luogu.com.cn/problem/P1892
*/

struct DisjointSetsUnion {
    std::vector<int> p;
    DisjointSetsUnion(int n): p(n) {
        std::iota(p.begin(), p.end(), 0);
    }
    DisjointSetsUnion() {

    }
    int find(int x) {
        return p[x] = (x == p[x] ? x : find(p[x]));
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        p[x] = y;
        return true;
    }
};
using DSU = DisjointSetsUnion;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(2 * n);
    for (int i = 0; i < m; i++) {
        char opt;
        std::cin >> opt;

        if (opt == 'F') {
            int x, y;
            std::cin >> x >> y;
            x--;
            y--;
            dsu.merge(x, y);
        } else if (opt == 'E') {
            int x, y;
            std::cin >> x >> y;
            x--;
            y--;
            dsu.merge(y + n, x); // 注意方向
            dsu.merge(x + n, y);
        }
    }

    int ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        ans += (int) (dsu.find(i) == i);
    }
    std::cout << ans << "\n";

    return 0;
}