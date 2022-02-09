#include <bits/stdc++.h>

template <typename T>
T quick_pow(T base, T exponent, T modulo)
{
    T result = 1;
    while (exponent)
    {
        if (exponent % 2 == 1) { result = result * base % modulo; }
        base = base * base % modulo; exponent /= 2;
    }
    return result % modulo;
}