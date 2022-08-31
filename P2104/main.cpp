#include <iostream>
#include <algorithm>

#define MAX_N 100002

struct Node {
    int l, r, cnt;
    Node *lson, *rson;

    Node(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {
        lson = rson = NULL;
    }
};

// 树根
Node *version[MAX_N];

Node *build(int l, int r) {
    if (l > r) return NULL;
    if (l == r) {
        return new Node(l, r, 0);
    }
    int mid = (l + r) >> 1;
    Node *cur = new Node(l, r, 0);
    cur->lson = build(l, mid);
    cur->rson = build(mid + 1, r);
    return cur;
}

inline void insert(int i, int l, int r, int d) {

    version[i] = new Node(l, r, version[i - 1]->cnt + 1);

    Node *pre = version[i - 1];
    Node *cur = version[i];

    int pre_cnt;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (d <= mid) {
            cur->rson = pre->rson;
            pre_cnt = pre->lson ? pre->lson->cnt + 1 : 1;
            cur->lson = new Node(l, mid, pre_cnt);
            cur = cur->lson, pre = pre->lson;
            r = mid;
        } else {
            cur->lson = pre->lson;
            pre_cnt = pre->rson ? pre->rson->cnt + 1 : 1;
            cur->rson = new Node(mid + 1, r, pre_cnt);
            cur = cur->rson, pre = pre->rson;
            l = mid + 1;
        }
    }
}

inline int find(int l, int r, int k) {

    Node *pre = version[l - 1];
    Node *cur = version[r];

    while (cur->lson) {
        int cur_l_cnt = cur->lson->cnt - pre->lson->cnt;
        if (k <= cur_l_cnt) {
            pre = pre->lson;
            cur = cur->lson;
        } else {
            k -= cur_l_cnt;
            pre = pre->rson;
            cur = cur->rson;
        }

    }
    return cur->l;
}

void display(Node *root) {

    if (!root) return;
    printf("[%d, %d], cnt=%d\n", root->l, root->r, root->cnt);

    display(root->lson);
    display(root->rson);
}

struct Point {
    int index, value;

    bool operator<(const Point &node) const {
        return value < node.value;
    }
};

int main() {

    freopen("../a.in", "r", stdin);

    int n, m, b[MAX_N];
    Point a[MAX_N];
    scanf("%d %d", &n, &m);

    // 离散
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].value);
        a[i].index = i;
    }
    std::sort(a, a + n);
    for (int i = 0; i < n; ++i) {
        b[a[i].index] = i + 1;
    }

    // 构建第一个空树
    version[0] = build(1, n);

    for (int i = 1; i <= n; ++i) {
        insert(i, 1, n, b[i - 1]);
//        printf("version %d, d=%d\n", i, b[i - 1]);
//        display(version[i]);
    }

    for (int i = 0; i < m; ++i) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", a[find(l, r, k) - 1].value);
    }


    return 0;
}
