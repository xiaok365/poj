#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

const int MAXN = 50001;

int parent[MAXN], parentRelation[MAXN], n;

int findRoot(int a) {

    if (a == parent[a]) return a;

    int tempParent = parent[a];
    parent[a] = findRoot(parent[a]);

    // 路径压缩，a与root的关系=a与父亲的关系+父亲与root的关系
    parentRelation[a] = (parentRelation[tempParent] + parentRelation[a]) % 3;
    return parent[a];
}

void unionSet(int a, int b, int relation) {

    int fa = findRoot(a);
    int fb = findRoot(b);

    if (fa == fb) {
        return;
    }
    // fa的父亲指向fa
    parent[fa] = fb;
    //a与fb的关系，a与b的关系+b与fb的关系
    int a2fb = relation + parentRelation[b];
    // fa与fb的关系，a与fb的关系-a与fa的关系
    parentRelation[fa] = (a2fb - parentRelation[a] + 3) % 3;
}


bool check(int a, int b, int relation) {
    if (a > n || b > n || a < 1 || b < 1) {
        return false;
    }
    if (relation == 1 && a == b) {
        return false;
    }
    int fa = findRoot(a);
    int fb = findRoot(b);
    if (fa == fb) {
        return (parentRelation[a] - parentRelation[b] + 3) % 3 == relation;
    }
    return true;
}

void init() {
    for (int i = 0; i < MAXN; ++i) {
        parent[i] = i;
        parentRelation[i] = 0;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int k, relation, a, b, lies = 0;

    init();
//    cin >> n >> k;
    scanf("%d%d", &n, &k);

    for (int i = 0; i < k; ++i) {
//        cin >> relation >> a >> b;
        scanf("%d%d%d", &relation, &a, &b);
        relation--;
        if (check(a, b, relation)) {
            unionSet(a, b, relation);
        } else {
            lies++;
//            cout << "i=" << i << ", d=" << relation << ", a=" << a << ", b=" << b << endl;
        }
    }


//    cout << lies << endl;
    printf("%d", lies);
    cin.close();
    cout.close();
    return 0;
}