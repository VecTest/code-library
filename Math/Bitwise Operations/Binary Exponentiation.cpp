#include <bits/stdc++.h>

template<typename Type>
Type quickPow(Type base, Type exponent, Type modulo)
{
    Type result = 1;
    while (exponent)
    {
        if (exponent % 2 == 1) { result = (result * base) % modulo; }
        base = (base * base) % modulo; exponent /= 2;
    }
    return result % modulo;
}