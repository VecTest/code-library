#include <bits/stdc++.h>

int power(int a, int b, int p) {
    int r = 1 % p;
    while (b) {
        if (b & 1) {
            r = (long long) r * a % p;
        }
        a = (long long) a * a % p;
        b >>= 1;
    }
    return r;
}

long long multiply(long long a, long long b, long long p) {
    long long r = 0;
    while (b) {
        if (b & 1) {
            r = (r + a) % p;
        }
        a = (a << 1) % p;
        b >>= 1;
    }
    return r;
}