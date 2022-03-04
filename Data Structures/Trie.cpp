#include <bits/stdc++.h>

struct Trie
{
    static const int N = 26;

    struct Node
    {
        Node *son[N];
        int key;
        Node()
        {
            key = 0;
            for (int i = 0; i < N; i++)
            {
                son[i] = nullptr;
            }
            return;
        }
    } * root;

    Trie()
    {
        root = new Node;
        return;
    }

    void insert(char *s, int k)
    {
        int l = strlen(s);
        Node *x = root;
        for (int i = 0; i < l; i++)
        {
            int y = s[i] - 'a';
            if (x->son[y] == nullptr)
            {
                x->son[y] = new Node;
            }
            x = x->son[y];
        }
        x->key = k;
        return;
    }

    int get(char *s)
    {
        int l = strlen(s);
        Node *x = root;
        for (int i = 0; i < l; i++)
        {
            int y = s[i] - 'a';
            if (x->son[y] == nullptr)
            {
                return 0;
            }
            x = x->son[y];
        }
        return x->key;
    }
};