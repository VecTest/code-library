#include <bits/stdc++.h>

int power(int base, int exponent, int modulo) {
    int result = 1 % modulo;
    while (exponent) {
        if (exponent & 1) {
            result = (long long) result * base % modulo;
        }
        base = (long long) base * base % modulo;
        exponent >>= 1;
    }
    return result;
}