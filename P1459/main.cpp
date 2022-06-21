#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 102;

void init(int map[][MAXN], int pre[]) {
    memset(map, 0, MAXN * MAXN * 4);
    memset(pre, -1, MAXN * 4);
}

int bfs(int map[][MAXN], int pre[], int source, int target, int m) {

    int queue[MAXN] = {0};
    bool visited[MAXN] = {false};
    int flow[MAXN] = {0};//flow[i]表示路径中到点i的最小可流通量

    int head = 0, tail = 1, current;
    queue[head] = source;
    visited[source] = true;
    flow[source] = 0x7fffffff;

    while (head < tail) {
        // 取队首
        current = queue[head++];
        // 如果已经到达汇点，证明已经找到了路
        if (current == target) {
            return flow[target];
        }
        for (int i = 0; i <= m; ++i) {
            if (!visited[i] && map[current][i] > 0) {
                queue[tail++] = i;
                pre[i] = current;
                flow[i] = min(flow[current], map[current][i]);
                visited[i] = true;
            }
        }
    }
    return 0;
}

int ek(int map[][MAXN], int pre[], int source, int target, int m) {

    int max_flow;
    int from, to, answer = 0;

    while ((max_flow = bfs(map, pre, source, target, m)) > 0) {
        answer += max_flow;
        // 增广
        to = target;
        while (pre[to] != -1) {
            from = pre[to];
            map[from][to] -= max_flow;
            map[to][from] += max_flow;
            to = from;
        }
    }
    return answer;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, p, c, m, i;
    int map[MAXN][MAXN], pre[MAXN];
    char ch;
    while (cin >> n >> p >> c >> m) {

        init(map, pre);
        int from, to, value;
        for (i = 0; i < m; ++i) {
            cin >> ch >> from >> ch >> to >> ch >> value;
            map[from + 1][to + 1] = value;
        }

        for (i = 0; i < p; ++i) {
            cin >> ch >> to >> ch >> value;
            map[0][to + 1] = value;
        }

        for (i = 0; i < c; ++i) {
            cin >> ch >> from >> ch >> value;
            map[from + 1][n + 1] = value;
        }
        cout << ek(map, pre, 0, n + 1, n + 1) << endl;
    }
    return 0;
}