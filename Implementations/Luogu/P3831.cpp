#include <bits/stdc++.h>

/*
大致思路：
分层图最短路

提交地址：
https://www.luogu.com.cn/problem/P3831
*/

const int N = 100;
const int INF = 1e9;

struct Edge {
	int v, w;
};

struct Vertex {
	int p, d;
	bool operator < (const Vertex &x) const {
		return d > x.d;
	}
};

struct Point {
    int x, y;
    int p;
};

bool cmp_x(Point &a, Point &b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp_y(Point &a, Point &b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

std::vector<int> Dijkstra(int n, int s, std::vector<std::vector<Edge>> &e) {
	std::vector<int> d(n, INF);
	d[s] = 0;

	std::vector<bool> f(n, false);

	std::priority_queue<Vertex> q;
	q.push({s, d[s]});

	while (!q.empty()) {
		int u = q.top().p;
		q.pop();

		if (f[u]) {
			continue;
		}
		f[u] = true;

		for (int i = 0; i < (int) e[u].size(); i++) {
			int v = e[u][i].v, w = e[u][i].w;
			if (!f[v] && d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({v, d[v]});
			}
		}
	}

	return d;
}

int main() {
    int n;
    scanf("%*d%d", &n);

    int s = n, t = n + 1;
    n += 2;

    std::vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;
        y--;
        a[i] = {x, y, i};
    }

    std::vector<std::vector<Edge>> e(n * 2);

    std::sort(a.begin(), a.end(), cmp_x);
    for (int i = 1; i < n; i++) {
        if (a[i].x == a[i - 1].x) {
            int p = a[i].p, q = a[i - 1].p;
            e[p].push_back({q, (a[i].y - a[i - 1].y) * 2});
            e[q].push_back({p, (a[i].y - a[i - 1].y) * 2});
        }
    }
    std::sort(a.begin(), a.end(), cmp_y);
    for (int i = 1; i < n; i++) {
        if (a[i].y == a[i - 1].y) {
            int p = a[i].p, q = a[i - 1].p;
            e[n + p].push_back({n + q, (a[i].x - a[i - 1].x) * 2});
            e[n + q].push_back({n + p, (a[i].x - a[i - 1].x) * 2});
        }
    }
    for (int i = 0; i < n; i++) {
        e[a[i].p].push_back({n + a[i].p, 1});
        e[n + a[i].p].push_back({a[i].p, 1});
    }
    e[s].push_back({n + s, 0});
    e[n + s].push_back({s, 0});
    e[t].push_back({n + t, 0});
    e[n + t].push_back({t, 0});

    std::vector<int> d = Dijkstra(n * 2, s, e);
    int ans = d[t];
    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }

#ifdef LOCAL
    system("pause");
#endif
    return 0;
}