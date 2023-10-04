#include <iostream>

using namespace std;

#define MAX_N 101

struct Point {
    int x, y;

    Point() : x(0), y(0) {}

    Point(int x, int y) : x(x), y(y) {}
};

int cnt, map[MAX_N][MAX_N], level_x[MAX_N], level_y[MAX_N], x[MAX_N], y[MAX_N];
bool visit_x[MAX_N], visit_y[MAX_N];

void init(int n, int m) {

    Point man[MAX_N], house[MAX_N];
    int man_cnt = 0, house_cnt = 0;
    char st[MAX_N];

    for (int i = 0; i < n; ++i) {
        scanf("%s", st);
        for (int j = 0; j < m; ++j) {
            if (st[j] == 'm') {
                man[man_cnt++] = Point(i, j);
            } else if (st[j] == 'H') {
                house[house_cnt++] = Point(i, j);
            }
        }
    }

    cnt = man_cnt;

    memset(level_y, 0, sizeof level_y);
    memset(level_x, 0x80, sizeof level_x);
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            map[i][j] = -(abs(house[j].x - man[i].x) + abs(house[j].y - man[i].y));
            level_x[i] = max(level_x[i], map[i][j]);
        }
    }
}

bool hungary(int u, int &min_slack) {
    visit_x[u] = true;
    for (int i = 0; i < cnt; ++i) {
        if (level_x[u] + level_y[i] == map[u][i]) {
            if (!visit_y[i]) {
                visit_y[i] = true;
                if (y[i] == -1 || hungary(y[i], min_slack)) {
                    x[u] = i;
                    y[i] = u;
                    return true;
                }
            }
        } else {
            min_slack = min(min_slack, level_x[u] + level_y[i] - map[u][i]);
        }
    }
    return false;
}

int km() {
    memset(x, 0xff, sizeof x);
    memset(y, 0xff, sizeof y);

    for (int i = 0; i < cnt; ++i) {
        while (true) {
            memset(visit_x, false, sizeof visit_x);
            memset(visit_y, false, sizeof visit_y);
            int min_slack = 0x7fffffff;
            // 找到匹配
            if (hungary(i, min_slack)) break;
            // 降低标准
            for (int j = 0; j < cnt; ++j) {
                if (visit_x[j]) level_x[j] -= min_slack;
                if (visit_y[j]) level_y[j] += min_slack;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < cnt; ++i) ans -= map[i][x[i]];
    return ans;
}

int main() {
    freopen("../a.in", "r", stdin);

    int n, m;
    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
        init(n, m);
        printf("%d\n", km());
    }

    return 0;
}
