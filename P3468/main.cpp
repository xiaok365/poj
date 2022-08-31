#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define LL long long

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

struct Node {
    LL left, right, total, extra;
    Node *lson, *rson;

    Node(LL l, LL r, LL t, LL c) : left(l), right(r), total(t), extra(c) {
        lson = rson = NULL;
    }
};

LL regionLength(Node *tree) {
    return tree->right - tree->left + 1;
}

void update(Node *root) {

    if (root->lson == NULL || root->rson == NULL || root->extra == 0) return;

    root->lson->total += root->extra * regionLength(root->lson);
    root->lson->extra += root->extra;
    root->rson->total += root->extra * regionLength(root->rson);
    root->rson->extra += root->extra;
    root->extra = 0;
}

Node *build(vector<LL> &num, LL l, LL r) {
    if (l > r) return NULL;
    if (l == r) return new Node(l, r, num[l], 0);

    Node *root = new Node(l, r, 0, 0);
    LL mid = (l + r) >> 1;
    root->lson = build(num, l, mid);
    root->rson = build(num, mid + 1, r);
    root->total = root->lson->total + root->rson->total;
    return root;
}

void add(Node *root, LL l, LL r, LL x) {
    if (root == NULL || root->right < l || root->left > r) {
        return;
    }
    if (root->left >= l && root->right <= r) {
        root->total += x * regionLength(root);
        if (root->left < root->right)root->extra += x;
        return;
    }
    update(root);
    add(root->lson, l, r, x);
    add(root->rson, l, r, x);
    root->total = root->lson->total + root->rson->total;
}

void query(Node *root, LL l, LL r, LL &sum) {
    if (root == NULL || root->right < l || root->left > r) {
        return;
    }
    if (root->left >= l && root->right <= r) {
        sum += root->total;
        return;
    }
    update(root);
    query(root->lson, l, r, sum);
    query(root->rson, l, r, sum);
}

void deleteMem(Node *root) {
    if (root == NULL)
        return;
    deleteMem(root->lson);
    deleteMem(root->rson);
    delete root;
};

void display(Node *root) {
    if (root == NULL)return;
    printf("left=%lld right=%lld total=%lld extra=%lld\n", root->left, root->right, root->total, root->extra);
    display(root->lson);
    display(root->rson);
}

int main() {
    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    LL n, q, i, a, b, c;
    char type;
    Node *root;

    read(n), read(q);

    vector<LL> num(n, 0);

    for (i = 0; i < n; i++) {
        read(num[i]);
    }

    n--;
    root = build(num, 0, n);

    for (i = 0; i < q; i++) {
        type = gc();

        while (type != 'Q' && type != 'C') type = gc();

        if (type == 'C') {
            read(a), read(b), read(c);
            add(root, a - 1, b - 1, c);
        } else {
            read(a), read(b);
            LL sum = 0;
            query(root, a - 1, b - 1, sum);
            printf("%lld\n", sum);
        }
    }

    return 0;
}