#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Edge {
    int start;
    int end;
    int value;
};
// 顶点个数
int p;

// 并查集根结点，初始为-1，合并之后为-num,num表示集合中的个数
int father[2500];

// 顶点i与顶点j之间的边长为   edge[i*N+j]
Edge edge[2500];

int answer, setNum;

void init() {
    answer = 0;
    setNum = 0;
    for (int i = 0; i < 2500; i++) {
        edge[i].start = i / p;
        edge[i].end = i % p;
        edge[i].value = 200;
        father[i] = -1;
    }
}

void input(ifstream &fin, ofstream &fout, int r) {
    int s, e, l;
    for (int i = 0; i < r; i++) {
        fin >> s >> e >> l;

        if (l < edge[(s - 1) * p + (e - 1)].value) {
            edge[(s - 1) * p + (e - 1)].value = l;
        }
    }
}

int findFather(int s) {
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

void unionSet(int s, int e) {

    int rootS = findFather(s);
    int rootE = findFather(e);

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

void kruskal(ofstream &fout) {

    int i, start, end;
    for (i = 0; i < p * p; i++) {
        start = edge[i].start;
        end = edge[i].end;
        if (start == end) {
            continue;
        }
        if (findFather(start) != findFather(end)) {
            unionSet(start, end);
            answer += edge[i].value;
            setNum++;
            if (setNum == p - 1) {
                fout << answer << endl;
                return;
            }
        }
    }

}

bool compare(const Edge &a, const Edge &b) {
    return a.value < b.value;
}

int main() {

    ifstream fin("../a.in");
    ofstream fout("../a.out");

    int r;

    fin >> p >> r;
    while (p != 0) {
        if (p == 1) {
            fout << 0 << endl;
            fin >> p >> r;
            continue;
        }
        init();
        input(fin, fout, r);
        sort(edge, edge + p * p, compare);
        kruskal(fout);
        fin >> p >> r;
    }

    fin.close();
    fout.close();

    return 0;
}