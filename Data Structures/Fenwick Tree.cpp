#include <bits/stdc++.h>

template <typename T>
struct FenwickTree
{
    int n;
    std::vector<T> a;

    FenwickTree()
    {
        return;
    }

    FenwickTree(int _n) : n(_n)
    {
        a.resize(n + 5);
        return;
    }

    void resize(int _n)
    {
        n = _n;
        a.resize(n + 5);
        return;
    }

    void modify(int x, T k)
    {
        while (x <= n)
        {
            a[x] += k;
            x += x & -x;
        }
        return;
    }

    T query(int x)
    {
        int s = 0;
        while (x > 0)
        {
            s += a[x];
            x -= x & -x;
        }
        return s;
    }

    T range_query(const int l, const int r)
    {
        return query(r) - query(l - 1);
    }

    void build(std::vector<int> b)
    {
        std::fill(a.begin(), a.end(), 0);
        for (int i = 1; i <= n; i++)
        {
            a[i] += b[i];
            if (i + (i & -i) <= n)
            {
                a[i + (i & -i)] += a[i];
            }
        }
        return;
    }
};