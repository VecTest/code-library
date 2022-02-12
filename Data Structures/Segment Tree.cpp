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
        long long key;
    };
    Node *a;

    void push_up(int x)
    {
        a[x].key = a[left].key + a[right].key;
        return;
    }

    void push_down(int x)
    {
        if (a[x].tag != 0 && a[x].l != a[x].r)
        {
            a[left].key += a[x].tag * (a[left].r - a[left].l + 1);
            a[left].tag += a[x].tag;

            a[right].key += a[x].tag * (a[right].r - a[right].l + 1);
            a[right].tag += a[x].tag;

            a[x].tag = 0;
        }
        return;
    }

    public:

    SegmentTree()
    {
        return;
    }

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

    void build(int x, int l, int r, const long long *input)
    {
        a[x].l = l, a[x].r = r;
        a[x].tag = 0;

        if (l == r)
        {
            a[x].key = input[l];
            return;
        }

        int m = (l + r) >> 1;
        build(left, l, m, input);
        build(right, m + 1, r, input);

        push_up(x);
        return;
    }

    long long query(int x, const int l, const int r)
    {
        if (a[x].l >= l && a[x].r <= r)
        {
            return a[x].key;
        }

        long long result = 0;

        push_down(x);
        if (a[left].r >= l)
        {
            result += query(left, l, r);
        }
        if (a[right].l <= r)
        {
            result += query(right, l, r);
        }

        return result;
    }

    void modify(int x, const int l, const int r, const long long k)
    {
        if (a[x].l >= l && a[x].r <= r)
        {
            a[x].key += k * (a[x].r - a[x].l + 1);
            a[x].tag += k;
            return;
        }

        push_down(x);
        if (a[left].r >= l)
        {
            modify(left, l, r, k);
        }
        if (a[right].l <= r)
        {
            modify(right, l, r, k);
        }
        push_up(x);

        return;
    }
};