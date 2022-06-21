#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define MAX_NODE 201
int map[MAX_NODE][MAX_NODE], pre[MAX_NODE];

int bfs(int source, int target, int m) {

    int queue[MAX_NODE] = {0};
    bool visited[MAX_NODE] = {false};
    int flow[MAX_NODE] = {0};//flow[i]表示路径中到点i的最小可流通量

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
        for (int i = 1; i <= m; ++i) {
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

int ek(int source, int target, int m) {

    int max_flow;
    int from, to, answer = 0;

    while ((max_flow = bfs(source, target, m)) > 0) {
        answer += max_flow;
        // 增广
        to = target;
        while (pre[to] != 0) {
            from = pre[to];
            map[from][to] -= max_flow;
            map[to][from] += max_flow;
            to = from;
        }
    }
    return answer;
}

int main() {

    ifstream fin("../a.in");
    ofstream fout("../a.out");
    int n, m, from, to, flow;

    while (fin >> n >> m) {
        // 数组初始化
        memset(map, 0, sizeof(map));

        for (int i = 0; i < n; ++i) {
            fin >> from >> to >> flow;
            map[from][to] += flow;
        }
        fout << ek(1, m, m) << endl;
    }
    return 0;
}