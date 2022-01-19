#include <bits/stdc++.h>

const int MaxN = 2e5 + 5, MaxM = 2e5 + 5;

struct Graph
{
    struct Edge
    {
        int to, dis, next;
    };
    Edge e[MaxM];
    int head[MaxN], cnt;
    void addEdge(int u, int v, int d)
    {
        cnt++;
        e[cnt].to = v;
        e[cnt].dis = d;
        e[cnt].next = head[u];
        head[u] = cnt;
        return;
    }
    Graph() { cnt = 0; }
};

struct Node
{
    int dis, pos;
    bool operator < (const Node &x) const
    {
        return dis > x.dis;
    }
};

std::vector<int> Dijkstra(int n, int m, int s, Graph g)
{
    bool vis[MaxN];
    std::vector<int> dis(n + 5);
    std::priority_queue<Node> q;

    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++) { dis[i] = INT_MAX; }
    dis[s] = 0;

    q.push((Node){0, s});

    while (!q.empty())
    {
        int p = q.top().pos;
        q.pop();

        if (vis[p]) { continue; }
        vis[p] = true;

        for (int i = g.head[p]; i; i = g.e[i].next)
        {
            int x = g.e[i].to, d = g.e[i].dis;
            if (!vis[x] && dis[x] > dis[p] + d)
            {
                dis[x] = dis[p] + d;
                q.push((Node){dis[x], x});
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
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        g.addEdge(u, v, d);
    }

    std::vector<int> dis = Dijkstra(n, m, s, g);

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    puts("");

    return 0;
}