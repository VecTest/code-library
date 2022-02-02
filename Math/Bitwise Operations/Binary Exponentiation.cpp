#include <bits/stdc++.h>

template <typename T>
T quick_pow(T base, T exponent, T modulo)
{
    T result = 1;
    while (exponent)
    {
        if (exponent % 2 == 1) { result = (result % modulo) * (base % modulo) % modulo; }
        base = (base % modulo) * (base % modulo) % modulo; exponent /= 2;
    }
    return result % modulo;
}