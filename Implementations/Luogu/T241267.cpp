#include <bits/stdc++.h>

/*
大致思路：
01 背包

提交地址：
https://www.luogu.com.cn/problem/T241267
*/

const int N = 1000;
const int M = 1000;
const int INF = 1e9;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	int w[N], v[N];
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &w[i], &v[i]);
	}

	int f[N + 1][M + 1];

	for (int i = 0; i <= M; i++) {
		f[0][i] = -INF;
	}
	f[0][0] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (j < w[i]) {
				f[i + 1][j] = f[i][j];
			} else {
				f[i + 1][j] = std::max(f[i][j], f[i][j - w[i]] + v[i]);
			}
		}
	}

	int ans = -INF;
	for (int i = 0; i <= m; i++) {
		ans = std::max(ans, f[n][i]);
	}
	printf("%d\n", ans);

#ifdef LOCAL
	system("pause");
#endif
	return 0;
}