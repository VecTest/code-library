#include <bits/stdc++.h>

const int N = 5e4;
const int MOD = 999983;

struct HashTable {
	std::vector<int> g[MOD];

	int H(int x) {
		return (x % MOD + MOD) % MOD;
	}

	bool insert(int x) {
		int p = H(x), n = (int) g[p].size();
		for (int i = 0; i < n; i++) {
			if (g[p][i] == x) {
				return false;
			}
		}
		g[p].push_back(x);
		return true;
	}

	bool exist(int x) {
	    int p = H(x), n = (int) g[p].size();
		for (int i = 0; i < n; i++) {
			if (g[p][i] == x) {
				return true;
			}
		}
		return false;
	}
};