#include <iostream>
#include <fstream>

using namespace std;

const int MAXM = 1001, MAXN = 102, INF = 0x7fffffff;

int m, n, pig[MAXM] = {0}, map[MAXN][MAXN] = {0}, d[MAXN] = {0};

bool bfs(int s, int t) {
    int queue[MAXN] = {0}, head = 0, tail = 1, current;
    bool visit[MAXN] = {false};
    queue[head] = s;
    d[s] = 0;
    visit[s] = true;

    while (head < tail) {
        // 取队首
        current = queue[head++];
        for (int i = 0; i <= n; ++i) {
            if (!visit[i] && map[current][i] > 0) {
                queue[tail++] = i;
                d[i] = d[current] + 1;
                visit[i] = true;
            }
        }
    }
    return visit[t];
}

int dfs(int u, int flow) {
    if (u == n || flow == 0) {
        return flow;
    }
    int temp = 0;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == d[u] + 1 && map[u][i] > 0) {
            int ret = dfs(i, min(flow - temp, map[u][i]));
            map[u][i] -= ret;
            map[i][u] += ret;
            temp += ret;
            if (flow == temp) {
                break;
            }
        }
    }
    return temp;
}

int dinic(int s, int t) {

    int ans = 0;
    while (bfs(s, t)) {
        ans += dfs(s, INF);
    }
    return ans;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int cnt, buy, k, visit[MAXM] = {0};
    cin >> m >> n;
    n++;

    for (int i = 1; i <= m; ++i) cin >> pig[i];
    for (int i = 1; i < n; ++i) {
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            cin >> k;
            if (visit[k] == 0) {
                map[0][i] += pig[k];
            } else {
                map[visit[k]][i] = INF;
            }
            visit[k] = i;
        }
        cin >> buy;
        map[i][n] = buy;
    }
    cout << dinic(0, n) << endl;
    return 0;
}