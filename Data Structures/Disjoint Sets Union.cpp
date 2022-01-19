#include <bits/stdc++.h>

const int MaxN = 5e3 + 5;

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

int main()
{
    int n, m, p;
    DisjointSetsUnion dsu;

    scanf("%d%d%d", &n, &m, &p);

    dsu.init(n);

    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        dsu.merge(x, y);
    }

    while (p--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        puts(dsu.get(x) == dsu.get(y) ? "Yes" : "No");
    }

    return 0;
}