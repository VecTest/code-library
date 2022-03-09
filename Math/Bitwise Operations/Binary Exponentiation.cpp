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