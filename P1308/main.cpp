#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100;

int father[MAXN], a[MAXN], total;
bool num[MAXN];

int findFather(int x) {
    if (father[x] == x) {
        return x;
    }
    int root = findFather(father[x]);
    father[x] = root;
    return father[x];
}

void unionSet(int a, int b) {
    int rootA = findFather(a);
    int rootB = findFather(b);
    if (rootA == rootB) {
        return;
    }
    father[rootB] = rootA;
}

void init() {
    for (int i = 0; i < MAXN; ++i) {
        num[i] = false;
        father[i] = i;
        a[i] = 0;
    }
    total = 0;
}

void put(int x) {
    if (!num[x]) {
        a[total++] = x;
        num[x] = true;
    }
}

bool isMultiRoot() {
    bool multiRoot = false;
    if (total < 2) return multiRoot;
    for (int i = 0; i < total - 1; ++i) {
        if (findFather(a[i]) != findFather(a[i + 1])) {
            multiRoot = true;
            break;
        }
    }
    return multiRoot;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a, b, i = 0;
    while (cin >> a >> b && a != -1 && b != -1) {
        init();
        bool isTree = true;
        while (a != 0 && b != 0) {
            if (isTree) {
                put(a);
                put(b);
                int rootA = findFather(a);
                int rootB = findFather(b);
                if ((rootA == rootB) || (rootB != b)) {
                    isTree = false;
                } else {
                    unionSet(a, b);
                }
                cin >> a >> b;
            } else {
                cin >> a >> b;
            }
        }

        if (isTree && !isMultiRoot()) {
            cout << "Case " << ++i << " is a tree." << endl;
        } else {
            cout << "Case " << ++i << " is not a tree." << endl;
        }
    }

    return 0;
}