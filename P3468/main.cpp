#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)

char buf[1 << 20], *p1 = buf, *p2 = buf;

template<typename T>
inline void read(T &x) {
    x = 0;
    char c = 0;
    bool minus = false;
    while (c < '0' || c > '9') {
        minus |= c == '-';
        c = gc();
    }
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (minus > 0) x = -x;
}

struct SegmentTree {
    long long left, right, total, childrenExtra;
    SegmentTree *lson, *rson;
};

long long regionLength(SegmentTree *tree) {
    return tree->right - tree->left + 1;
}

void updateChildren(SegmentTree *root) {
    if (root->lson != NULL && root->rson != NULL && root->childrenExtra != 0) {
        root->lson->total += root->childrenExtra * regionLength(root->lson);
        root->lson->childrenExtra += root->childrenExtra;
        root->rson->total += root->childrenExtra * regionLength(root->rson);
        root->rson->childrenExtra += root->childrenExtra;
        root->childrenExtra = 0;
    }
}

SegmentTree *buildTree(vector<long long> &num, long long l, long long r) {
    if (l > r) {
        return NULL;
    }
    if (l == r) {
        SegmentTree *root = new SegmentTree;
        root->left = l;
        root->right = r;
        root->total = num[l];
        root->childrenExtra = 0;
        root->lson = NULL;
        root->rson = NULL;
        return root;
    }
    SegmentTree *root = new SegmentTree;
    root->left = l;
    root->right = r;
    root->childrenExtra = 0;
    long long mid = (l + r) >> 1;
    root->lson = buildTree(num, l, mid);
    root->rson = buildTree(num, mid + 1, r);
    root->total = root->lson->total + root->rson->total;
    return root;
}

void addRegion(SegmentTree *root, long long regionLeft, long long regionRight, long long addNum) {
    if (root == NULL || root->right < regionLeft || root->left > regionRight) {
        return;
    }
    if (root->left >= regionLeft && root->right <= regionRight) {
        root->total += addNum * regionLength(root);
        if (root->left < root->right)root->childrenExtra += addNum;
        return;
    }
    updateChildren(root);
    addRegion(root->lson, regionLeft, regionRight, addNum);
    addRegion(root->rson, regionLeft, regionRight, addNum);
    root->total = root->lson->total + root->rson->total;
}

void queryRegion(SegmentTree *root, long long regionLeft, long long regionRight, long long &sum) {
    if (root == NULL || root->right < regionLeft || root->left > regionRight) {
        return;
    }
    if (root->left >= regionLeft && root->right <= regionRight) {
        sum += root->total;
        return;
    }
    updateChildren(root);
    queryRegion(root->lson, regionLeft, regionRight, sum);
    queryRegion(root->rson, regionLeft, regionRight, sum);
}

void deleteMem(SegmentTree *root) {
    if (root == NULL)
        return;
    deleteMem(root->lson);
    deleteMem(root->rson);
    delete root;
};

void printTree(ofstream &cout, SegmentTree *root) {
    if (root == NULL)return;
    cout << "left=" << root->left << "right=" << root->right
         << "total=" << root->total << "extra=" << root->childrenExtra << endl;
    printTree(cout, root->lson);
    printTree(cout, root->rson);
}

//inline long long read() {
//    long long x = 0;
//    char ch = 0;
//    bool minus = false;
//
//    while (ch < '0' || ch > '9') {
//        minus = ch == '-';
//        ch = getchar();
//    }
//    while (ch >= '0' && ch <= '9') {
//        x = (x << 3) + (x << 1) + (ch ^ 48);
//        ch = getchar();
//    }
//    return minus ? -x : x;
//}



int main() {
//    ifstream cin("../a.in");
//    ofstream cout("../a.out");

    long long n, q, i, a, b, c;
    char type;
    SegmentTree *root;

#ifndef xiaok
    freopen("a.in", "r", stdin);
#endif
//    scanf("%lld%lld", &n, &q);
//    cin >> n >> q;
//    n = read();
//    q = read();
    read(n), read(q);

    vector<long long> num(n, 0);

    for (i = 0; i < n; i++) {
//        scanf("%lld", &num[i]);
//        cin >> num[i];
//        num[i] = read();
        read(num[i]);
//        cout << num[i] << endl;
    }

    n--;
    root = buildTree(num, 0, n);

    for (i = 0; i < q; i++) {
//        scanf("%c", &type);
//        cin >> type;
        type = gc();
//        read(type);

        while (type != 'Q' && type != 'C') {
            type = gc();
        }

        if (type == 'C') {
//            scanf("%lld%lld%lld", &a, &b, &c);
//            cin >> a >> b >> c;
//            a = read(), b = read(), c = read();
            read(a), read(b), read(c);
//            cout << a << " " << b << " " << c << endl;
            addRegion(root, a - 1, b - 1, c);
        } else {
//            scanf("%lld%lld", &a, &b);
//            cin >> a >> b;
//            a = read(),b = read();
            read(a), read(b);
//            cout << a << " " << b << endl;
            long long sum = 0;
            queryRegion(root, a - 1, b - 1, sum);
            printf("%lld\n", sum);
//            cout << sum << endl;
        }
    }

    return 0;
}