#include <bits/stdc++.h>

const int MaxN = 1e4 + 5, MaxM = 5e5 + 5;

struct Graph
{
    struct Edge
    {
        int from, to, dis;
    };
    Edge e[MaxM];
};

std::vector<int> BellmanFord(int n, int m, int s, Graph g)
{
    bool f = true;
    std::vector<int> dis(n + 5);

    for (int i = 1; i <= n; i++) { dis[i] = INT_MAX; }
    dis[s] = 0;

    for (int i = 1; i <= n && f; i++)
    {
        f = false;
        for (int j = 0; j < m; j++)
        {
            if (dis[g.e[j].from] == INT_MAX) { continue; }
            else if (dis[g.e[j].to] > dis[g.e[j].from] + g.e[j].dis)
            {
                dis[g.e[j].to] = dis[g.e[j].from] + g.e[j].dis;
                f = true;
            }
        }
    }

    return dis;
}

int main()
{
    int n, m, s;
    Graph g;

    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &g.e[i].from, &g.e[i].to, &g.e[i].dis);
    }

    std::vector<int> dis = BellmanFord(n, m, s, g);

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    puts("");

    return 0;
}