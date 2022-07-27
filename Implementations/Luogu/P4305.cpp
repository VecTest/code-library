#include <bits/stdc++.h>

/*
大致思路：
哈希表

提交地址：
https://www.luogu.com.cn/problem/P4305
*/

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
};

void solve() {
	int n;
	scanf("%d", &n);

	HashTable t;
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		if (t.insert(x)) {
			printf("%d ", x);
		}
	}
	puts("");
}

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		solve();
	}

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}