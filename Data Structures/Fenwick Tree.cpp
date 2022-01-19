#include <bits/stdc++.h>

const int MaxN = 5e5 + 5;

struct FenwickTree
{
    int a[MaxN], size;
    int lowbit(int x) { return x & -x; }
    void init(int n, int *b)
    {
        size = n;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
        {
            a[i] += b[i];
            a[i + lowbit(i)] += a[i];
        }
        return;
    }
    void modify(int x, int v)
    {
        while (x <= size)
        {
            a[x] += v;
            x += lowbit(x);
        }
        return;
    }
    int search(int x)
    {
        int s = 0;
        while (x)
        {
            s += a[x];
            x -= lowbit(x);
        }
        return s;
    }
    int query(int l, int r)
    {
        return search(r) - search(l - 1);
    }
};


int main()
{
    int n, m;
    int b[MaxN];
    FenwickTree ft;

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }

    ft.init(n, b);

    while (m--)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            int x, v;
            scanf("%d%d", &x, &v);
            ft.modify(x, v);
        }
        else if (opt == 2)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", ft.query(l, r));
        }
    }

    return 0;
}