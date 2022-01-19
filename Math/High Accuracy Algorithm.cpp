#include <bits/stdc++.h>

static const int Len = 1e4 + 5;

struct BigInt
{
    static const int Bit = 9;
    static const long long Mod = 1000000000;

    long long s[Len], c;
    bool flag;

    BigInt operator = (const char *num)
    {
        memset(s, 0, sizeof(s)); flag = (num[0] != 45);

        int l = strlen(num);
        c = 0;
        for (int i = l - 1; i >= int(!flag); i -= Bit)
        {
            c++;
            long long w = 1;
            for (int j = i; j > i - Bit && j >= int(!flag); j--)
            {
                s[c] += (num[j] ^ 48) * w;
                w = (w << 1) + (w << 3);
            }
        }
        return *this;
    }
    BigInt operator = (const int num)
    {
        char a[Len];
        sprintf(a, "%d", num);
        *this = a;
        return *this;
    }
    BigInt operator = (const long long num)
    {
        char a[Len];
        sprintf(a, "%lld", num);
        *this = a;
        return *this;
    }
    BigInt() { memset(s, 0, sizeof(s)); c = 1; }
    BigInt(const char *num) { *this = num; }
    BigInt(const int num) { *this = num; }
    BigInt(const long long num) { *this = num; }

    friend bool _equal(const BigInt &a, const BigInt &b)
    {
        if (a.c != b.c) { return false; }
        int l = std::max(a.c, b.c);
        for (int i = l; i >= 1; i--)
        {
            if (a.s[i] != b.s[i]) { return false; }
        }
        return true;
    }
    friend bool _greater(const BigInt &a, const BigInt &b)
    {
        if (a.c != b.c) { return a.c > b.c; }
        int l = std::max(a.c, b.c);
        for (int i = l; i >= 1; i--)
        {
            if (a.s[i] != b.s[i]) { return a.s[i] > b.s[i]; }
        }
        return false;
    }
    friend bool _less(const BigInt &a, const BigInt &b)
    {
        if (a.c != b.c) { return a.c < b.c; }
        int l = std::max(a.c, b.c);
        for (int i = l; i >= 1; i--)
        {
            if (a.s[i] != b.s[i]) { return a.s[i] < b.s[i]; }
        }
        return false;
    }

    friend bool operator == (const BigInt &a, const BigInt &b)
    {
        if (a.flag == b.flag) { return _equal(a, b); }
        else { return false; }
    }
    friend bool operator > (const BigInt &a, const BigInt &b)
    {
        if (a.flag && !b.flag) { return true; }
        if (a.flag && b.flag) { return _greater(a, b); }
        if (!a.flag && b.flag) { return false; }
        if (!a.flag && !b.flag) { return _less(a, b); }
    }
    friend bool operator < (const BigInt &a, const BigInt &b)
    {
        if (a.flag && !b.flag) { return false; }
        if (a.flag && b.flag) { return _less(a, b); }
        if (!a.flag && b.flag) { return true; }
        if (!a.flag && !b.flag) { return _greater(a, b); }
    }
    friend bool operator >= (const BigInt &a, const BigInt &b) { return (a > b || a == b); }
    friend bool operator <= (const BigInt &a, const BigInt &b) { return (a < b || a == b); }

    friend BigInt _plus(const BigInt &a, const BigInt &b)
    {
        BigInt c;
        c.c = std::max(a.c, b.c) + 1;
        long long x = 0;
        for (int i = 1; i <= c.c; i++)
        {
            c.s[i] = a.s[i] + b.s[i] + x;
            x = c.s[i] / Mod;
            c.s[i] %= Mod;
        }
        while (c.s[c.c] == 0 && c.c > 1) { c.c--; }
        return c;
    }
    friend BigInt _subtract(const BigInt &a, const BigInt &b) // a - b (a > b)
    {
        BigInt c;
        c.c = std::max(a.c, b.c);
        for (int i = 1; i <= c.c; i++)
        {
            c.s[i] += a.s[i] - b.s[i];
            if (c.s[i] < 0)
            {
                c.s[i] += Mod;
                c.s[i + 1]--;
            }
        }
        while (c.s[c.c] == 0 && c.c > 1) { c.c--; }
        return c;
    }
    friend BigInt _multiply(const BigInt &a, const BigInt &b)
    {
        BigInt c;
        c.c = a.c + b.c;
        for (int i = 1; i <= a.c; i++)
        {
            long long x = 0;
            for (int j = 1; j <= b.c; j++)
            {
                int k = i + j - 1;
                c.s[k] += a.s[i] * b.s[j] + x;
                x = c.s[k] / Mod;
                c.s[k] %= Mod;
            }
            c.s[i + b.c] = x;
        }
        while (c.s[c.c] > 0) { c.c++; }
        while (c.s[c.c] == 0 && c.c > 1) { c.c--; }
        return c;
    }

    friend BigInt operator + (const BigInt &a, const BigInt &b)
    {
        BigInt c;
        if (a.flag && b.flag) { c = _plus(a, b); c.flag = true; }
        if (a.flag && !b.flag)
        {
            if (_greater(a, b)) { c = _subtract(a, b); c.flag = true; }
            if (_equal(a, b)) { c = 0; c.flag = true; }
            if (_less(a, b)) { c = _subtract(b, a); c.flag = false; }
        }
        if (!a.flag && b.flag)
        {
            if (_greater(a, b)) { c = _subtract(a, b); c.flag = false; }
            if (_equal(a, b)) { c = 0; c.flag = true; }
            if (_less(a, b)) { c = _subtract(b, a); c.flag = true; }
        }
        if (!a.flag && !b.flag) { c = _plus(a, b); c.flag = false; }
        return c;
    }
    BigInt operator += (const BigInt &a)
    {
        *this = *this + a;
        return *this;
    }
    friend BigInt operator - (const BigInt &a, const BigInt &b)
    {
        BigInt c;
        if (a.flag && b.flag)
        {
            if (_greater(a, b)) { c = _subtract(a, b); c.flag = true; }
            if (_equal(a, b)) { c = 0; c.flag = true; }
            if (_less(a, b)) { c = _subtract(b, a); c.flag = false; }
        }
        if (a.flag && !b.flag) { c = _plus(a, b); c.flag = true; }
        if (!a.flag && b.flag) { c = _plus(a, b); c.flag = false; }
        if (!a.flag && !b.flag)
        {
            if (_greater(a, b)) { c = _subtract(a, b); c.flag = false; }
            if (_equal(a, b)) { c = 0; c.flag = true; }
            if (_less(a, b)) { c = _subtract(b, a); c.flag = true; }
        }
        return c;
    }
    BigInt operator -= (const BigInt &a)
    {
        *this = *this - a;
        return *this;
    }
    friend BigInt operator * (const BigInt &a, const BigInt &b)
    {
        BigInt c;
        if (a.flag ^ b.flag) { c = _multiply(a, b); c.flag = false; }
        else { c = _multiply(a, b); c.flag = true; }
        return c;
    }
    BigInt operator *= (const BigInt &a)
    {
        *this = *this * a;
        return *this;
    }
};

std::ostream& operator << (std::ostream &out, const BigInt &a)
{
    if (!a.flag) putchar(45);
    printf("%lld", a.s[a.c]);
    for (int i = a.c - 1; i >= 1; i--) { printf("%09lld", a.s[i]); }
    return out;
}
std::istream& operator >> (std::istream &in, BigInt &a)
{
    char s[Len];
    in >> s;
    a = s;
    return in;
}