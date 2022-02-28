#include <bits/stdc++.h>

struct SparseTable
{
private:
    int n, k;
    std::vector<int> lg;
    std::vector<std::vector<int>> f;

    int function(int a, int b)
    {
        // your code goes here
        return std::min(a, b);
    }

public:
    SparseTable()
    {
        return;
    }

    SparseTable(int x)
    {
        n = x;

        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
        {
            lg[i] = lg[i >> 1] + 1;
        }

        k = lg[n];
        return;
    }

    void assign(int x)
    {
        n = x;

        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
        {
            lg[i] = lg[i >> 1] + 1;
        }

        k = lg[n];
        return;
    }

    void build(std::vector<int> &a)
    {
        f.assign(n + 1, std::vector<int>(k + 1));
        for (int i = 1; i <= n; i++)
        {
            f[i][0] = a[i];
        }
        for (int j = 1; j <= k; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                f[i][j] = function(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
        return;
    }

    int query(const int l, const int r)
    {
        int x = lg[r - l + 1];
        int result = function(f[l][x], f[r - (1 << x) + 1][x]);
        return result;
    }
};