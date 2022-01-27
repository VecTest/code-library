#include <bits/stdc++.h>

struct DisjointSetsUnion
{
    static const int MaxN = 5e3 + 5;
    int p[MaxN], r[MaxN];
    void build(int n)
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