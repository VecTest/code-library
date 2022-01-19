#include <bits/stdc++.h>

const int MaxN = 1e8 + 5;

std::vector<int> Euler(int n)
{
    bool numList[MaxN];
    std::vector<int> primes;

    memset(numList, true, sizeof(numList));
    numList[0] = numList[1] = false;

    int count = 0;

    for (int i = 2; i <= n; i++)
    {
        if (numList[i])
        {
            primes.push_back(i);
            count++;
        }
        for (int j = 0; j < count && i * primes[j] <= n; j++)
        {
            numList[i * primes[j]] = false;
            if (i % primes[j] == 0)
            {
                break;
            }
        }
    }

    return primes;
}