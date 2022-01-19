#include <bits/stdc++.h>

const int MaxN = 1e8 + 5;

std::vector<int> Eratosthenes(int n)
{
    bool numList[MaxN];
    std::vector<int> primes;

    memset(numList, true, sizeof(numList));
    numList[0] = numList[1] = false;

    for (int i = 2; i * i <= n; i++)
    {
        if (numList[i] == false) { continue; }
        for (int j = i * i; j <= n; j += i)
        {
            numList[j] = false;
        }
    }

    for (int i = 2; i <= n; i++)
    {
        if (numList[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}