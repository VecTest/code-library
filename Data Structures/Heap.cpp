#include <bits/stdc++.h>

template <typename T>
struct MinHeap
{
private:
    T *a;
    int _size;

    int son(int x)
    {
        return x << 1 | ((x << 1 | 1) <= _size && a[x << 1] > a[x << 1 | 1]);
    }

    void swim(int x)
    {
        for (int i = x; i > 1 && a[i] < a[i >> 1]; i >>= 1)
        {
            std::swap(a[i], a[i >> 1]);
        }
        return;
    }

    void sink(int x)
    {
        for (int i = x, t = son(i); t <= _size && a[i] > a[t]; i = t, t = son(i))
        {
            std::swap(a[i], a[t]);
        }
        return;
    }

public:
    MinHeap()
    {
        return;
    }

    MinHeap(int n)
    {
        _size = 0;
        a = new T[n + 5];
        return;
    }

    ~MinHeap()
    {
        delete a;
        return;
    }

    void assign(int n)
    {
        _size = 0;
        a = new T[n + 5];
        return;
    }

    T top()
    {
        return a[1];
    }

    int size()
    {
        return _size;
    }

    bool empty()
    {
        return !_size;
    }

    void push(T k)
    {
        a[++_size] = k;
        swim(_size);
        return;
    }

    void pop()
    {
        assert(_size);
        a[1] = a[_size--];
        sink(1);
        return;
    }
};