#include <bits/stdc++.h>

struct SegmentTree
{
    private:

    #define left x << 1
    #define right x << 1 | 1

    struct Node
    {
        int l, r;
        long long tag;
        long long sum;
    };
    Node *a;

    void push_up(int x)
    {
        a[x].sum = a[left].sum + a[right].sum;
        return;
    }

    void push_down(int x)
    {
        if (a[x].tag != 0 && a[x].l != a[x].r)
        {
            a[left].sum += a[x].tag * (a[left].r - a[left].l + 1);
            a[left].tag += a[x].tag;

            a[right].sum += a[x].tag * (a[right].r - a[right].l + 1);
            a[right].tag += a[x].tag;

            a[x].tag = 0;
        }
        return;
    }

    public:

    SegmentTree() { return; }

    SegmentTree(int n)
    {
        a = new Node[n << 2 | 1];
        return;
    }

    ~SegmentTree()
    {
        delete a;
        return;
    }

    void assign(int n)
    {
        a = new Node[n << 2 | 1];
        return;
    }

    void build(int x, int l, int r, long long *input)
    {
        a[x].l = l, a[x].r = r;
        a[x].tag = 0;

        if (l == r)
        {
            a[x].sum = input[l];
            return;
        }

        int m = (l + r) >> 1;
        build(left, l, m, input);
        build(right, m + 1, r, input);

        push_up(x);
        return;
    }

    long long query(int x, int sl, int sr)
    {
        if (a[x].l >= sl && a[x].r <= sr)
        {
            return a[x].sum;
        }

        long long result = 0;

        push_down(x);
        if (a[left].r >= sl)
        {
            result += query(left, sl, sr);
        }
        if (a[right].l <= sr)
        {
            result += query(right, sl, sr);
        }

        return result;
    }

    void modify(int x, int sl, int sr, long long delta)
    {
        if (a[x].l >= sl && a[x].r <= sr)
        {
            a[x].sum += delta * (a[x].r - a[x].l + 1);
            a[x].tag += delta;
            return;
        }

        push_down(x);
        if (a[left].r >= sl)
        {
            modify(left, sl, sr, delta);
        }
        if (a[right].l <= sr)
        {
            modify(right, sl, sr, delta);
        }
        push_up(x);

        return;
    }
};