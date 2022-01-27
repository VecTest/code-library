#include <bits/stdc++.h>

template<typename T>
struct SegmentTree
{
    static const int N = 2e5 + 5;

    struct Node
    {
        int l, r;
        T s, t;
    };
    Node a[N << 2];

    void push_up(int x)
    {
        a[x].s = a[x << 1].s + a[x << 1 | 1].s;
        return;
    }

    void push_down(int x)
    {
        Node &root = a[x], &left = a[x << 1], &right = a[x << 1 | 1];
        if (root.t != 0 && root.l != root.r)
        {
            left.s += root.t * (left.r - left.l + 1);
            left.t += root.t;

            right.s += root.t * (right.r - right.l + 1);
            right.t += root.t;

            root.t = 0;
        }
        return;
    }

    void build(int x, int l, int r, T *b)
    {
        a[x].l = l, a[x].r = r, a[x].t = 0;

        if (l == r)
        {
            a[x].s = b[l];
            return;
        }

        int m = (l + r) >> 1;
        build(x << 1, l, m, b);
        build(x << 1 | 1, m + 1, r, b);

        push_up(x);

        return;
    }

    void modify(int x, int sl, int sr, T k)
    {
        Node &root = a[x], &left = a[x << 1], &right = a[x << 1 | 1];

        if (root.l >= sl && root.r <= sr)
        {
            root.s += k * (root.r - root.l + 1);
            root.t += k;
            return;
        }

        push_down(x);
        if (left.r >= sl)
        {
            modify(x << 1, sl, sr, k);
        }
        if (right.l <= sr)
        {
            modify(x << 1 | 1, sl, sr, k);
        }
        push_up(x);

        return;
    }

    T query(int x, int sl, int sr)
    {
        Node &root = a[x], &left = a[x << 1], &right = a[x << 1 | 1];

        if (root.l >= sl && root.r <= sr)
        {
            return root.s;
        }

        T result = 0;

        push_down(x);
        if (left.r >= sl)
        {
            result += query(x << 1, sl, sr);
        }
        if (right.l <= sr)
        {
            result += query(x << 1 | 1, sl, sr);
        }

        return result;
    }
};