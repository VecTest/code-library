#include <bits/stdc++.h>

struct Trie
{
private:
    static constexpr int N = 1 << 7 | 1;

    int _size;
    int *a[N];
    int *tag;

public:
    Trie()
    {
        return;
    }

    Trie(int n)
    {
        for (int i = 0; i < N; i++)
        {
            a[i] = new int[n + 5];
        }
        tag = new int[n + 5];

        _size = 0;
        for (int i = 0; i < N; i++)
        {
            memset(a[i], 0, sizeof(int) * (n + 5));
        }
        memset(tag, false, sizeof(int) * (n + 5));
        return;
    }

    ~Trie()
    {
        for (int i = 0; i < N; i++)
        {
            delete a[i];
        }
        delete tag;
        return;
    }

    void assign(int n)
    {
        for (int i = 0; i < N; i++)
        {
            a[i] = new int[n + 5];
        }
        tag = new int[n + 5];

        _size = 0;
        for (int i = 0; i < N; i++)
        {
            memset(a[i], 0, sizeof(int) * (n + 5));
        }
        memset(tag, 0, sizeof(int) * (n + 5));
        return;
    }

    void insert(char *s, int k)
    {
        int x = 0, l = strlen(s);
        for (int i = 0; i < l; i++)
        {
            int c = s[i];
            if (!a[c][x])
            {
                a[c][x] = ++_size;
            }
            x = a[c][x];
        }
        tag[x] = k;
        return;
    }

    int get(char *s)
    {
        int x = 0, l = strlen(s);
        for (int i = 0; i < l; i++)
        {
            int c = s[i];
            if (!a[c][x])
            {
                return 0;
            }
            x = a[c][x];
        }
        return tag[x];
    }
};