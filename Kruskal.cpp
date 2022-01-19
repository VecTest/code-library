#include <bits/stdc++.h>

const int MaxN = 5e3 + 5, MaxM = 2e5 + 5;

struct DisjointSetsUnion
{
    int p[MaxN], r[MaxN];
    void init(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            p[i] = i; r[i] = 1;
        }
        return;
    }
    int get(int x)
    {
        return p[x] = (x == p[x] ? x : get(p[x]));
    }
    void merge(int x, int y)
    {
        int a = get(x), b = get(y);

        if (a == b) { return; }

        if (r[a] == r[b]) { r[a]++; }
        if (r[a] >= r[b])
        {
            p[b] = a;
        }
        else if (r[a] < r[b])
        {
            p[a] = b;
        }

        return;
    }
};

struct Edge
{
    int u, v, d;
    bool operator < (const Edge &x) const
    {
        return d < x.d;
    }
};

int Kruskal(int n, int m, Edge *e)
{
    int count = 0, dis = 0;
    DisjointSetsUnion dsu;

    dsu.init(n);
    std::sort(e, e + m);

    for (int i = 0; i < m; i++)
    {
        int u = dsu.get(e[i].u), v = dsu.get(e[i].v);
        if (u == v) { continue; }
        dis += e[i].d;
        dsu.merge(e[i].u, e[i].v);
        if (++count == n - 1) { break; }
    }

    return count == n - 1 ? dis : -1;
}

int main()
{
    int n, m;
    Edge e[MaxM];

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].d);
    }

    int dis = Kruskal(n, m, e); // if dis equals to -1, then the gragh is not connected

    printf("%d\n", dis);

    return 0;
}