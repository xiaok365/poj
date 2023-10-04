#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 30001;

int findFather(int father[], int s) {
    int root = s, temp;
    // 查找s的最顶层根
    while (father[root] >= 0) {
        root = father[root];
    }
    // 路径压缩，提高后续查找效率
    while (s != root) {
        temp = father[s];
        father[s] = root;
        s = temp;
    }
    return root;
}

void unionSet(int father[], int s, int e) {
    int rootS = findFather(father, s);
    int rootE = findFather(father, e);
    if (rootS == rootE) return;
    int newFather = father[rootS] + father[rootE];
    // 将结点数少的集合作为结点数多的集合的儿子节点
    if (father[rootS] > father[rootE]) {
        father[rootS] = rootE;
        father[rootE] = newFather;
    } else {
        father[rootE] = rootS;
        father[rootS] = newFather;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m, cnt;
    int father[MAXN];

    while (cin >> n >> m && n != 0 || m != 0) {
        memset(father, 0xff, MAXN * 4);
        while (m--) {
            cin >> cnt;
            int pre = -1, now;
            for (int i = 0; i < cnt; ++i) {
                cin >> now;
                if (pre != -1) {
                    unionSet(father, pre, now);
                }
                pre = now;
            }
        }
        cout << -father[findFather(father, 0)] << endl;
    }
    return 0;
}