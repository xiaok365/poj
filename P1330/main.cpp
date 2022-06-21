#include <iostream>
#include <fstream>

using namespace std;

const int MAXM = 10001;

struct Edge {
    int to;
    int next;
};

// 所有的边集
Edge edge[MAXM];
// head[i] 顶点i的第一条边的索引，即edge的下标
int head[MAXM], father[MAXM], inDegree[MAXM] = {0}, edgeCnt, one, two, n;
bool visit[MAXM];

void init() {
    edgeCnt = 0;
    for (int i = 0; i <= n; ++i) {
        head[i] = -1;
        father[i] = i;
        inDegree[i] = 0;
        visit[i] = false;
    }
}

void addEdge(int a, int b) {
    edge[edgeCnt].to = b;
    edge[edgeCnt++].next = head[a];
    head[a] = edgeCnt - 1;
    inDegree[b]++;
}

int findRoot() {
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            return i;
        }
    }
    return 0;
}

int findFather(int x) {
    if (father[x] == x) return x;
    int root = findFather(father[x]);
    father[x] = root;
    return root;
}

void unionFather(int x, int y) {

    int parentX = findFather(x);
    int parentY = findFather(y);
    if (parentX == parentY) return;
    father[parentY] = parentX;
}

void query(int root, int &ans) {

    if (ans != -1) return;
    visit[root] = true;
    int temp = head[root];

    if (visit[one] && visit[two]) {
        if (root == one) ans = findFather(two);
        else ans = findFather(one);
        return;
    }

    while (temp != -1) {
        query(edge[temp].to, ans);
        unionFather(root, edge[temp].to);
        temp = edge[temp].next;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, a, b;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        init();
        for (int j = 0; j < n - 1; ++j) {
            cin >> a >> b;
            addEdge(a, b);
        }
        cin >> one >> two;
        int ans = -1;
        query(findRoot(), ans);
        cout << ans << endl;
    }

    return 0;
}