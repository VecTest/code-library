#include <bits/stdc++.h>

template <typename Type>
struct SegmentTree
{
    const int MaxN = 1e5 + 5;

    #define ls (x << 1)
    #define rs (x << 1 | 1)

    struct Node
    {
        int l, r;
        Type t;
        Type d;
    };
    Node a[MaxN];

    void pushUp(int x)
    {
        a[x].d = a[ls].d + a[rs].d;
        return;
    }

    void pushDown(int x)
    {
        if (a[x].t)
        {
            a[ls].d += a[x].t * (a[ls].r - a[ls].l + 1);
            a[ls].t += a[x].t;

            a[rs].d += a[x].t * (a[rs].r - a[rs].l + 1);
            a[rs].t += a[x].t;

            a[x].t = 0;
        }
        return;
    }

    void build(int x, int l, int r, Type *b)
    {
        a[x].l = l; a[x].r = r; a[x].t = 0;

        if (l == r)
        {
            a[x].d = b[l];
            return;
        }

        int m = r + ((l - r) >> 1);
        build(ls, l, m, b);
        build(rs, m + 1, r, b);

        pushUp(x);

        return;
    }

    Type query(int x, int sl, int sr)
    {
        if (a[x].l >= sl && a[x].r <= sr)
        {
            return a[x].d;
        }

        pushDown(x);

        Type result = 0;

        if (a[ls].r >= sl)
        {
            result += query(ls, sl, sr);
        }
        if (a[rs].l <= sr)
        {
            result += query(rs, sl, sr);
        }

        return result;
    }

    void modify(int x, int sl, int sr, Type delta)
    {
        if (a[x].l >= sl && a[x].r <= sr)
        {
            a[x].d += (a[x].r - a[x].l + 1) * delta;
            a[x].t += delta;
            return;
        }

        pushDown(x);

        if (a[ls].r >= sl)
        {
            modify(ls, sl, sr, delta);
        }
        if (a[rs].l <= sr)
        {
            modify(rs, sl, sr, delta);
        }

        pushUp(x);

        return;
    }
};