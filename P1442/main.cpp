#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX_N 30001

struct Node {
    int key, priority, cnt;
    Node *lson, *rson;

    Node() : key(0), priority(0), cnt(0) {
        lson = rson = NULL;
    }

    Node(int k, int p) : key(k), priority(p), cnt(1) {
        lson = rson = NULL;
    }
};

Node *left_rotate(Node *x) {
    Node *y = x->rson;
    if (y) {
        x->rson = y->lson;
        x->cnt -= y->cnt;
        if (y->lson) {
            x->cnt += y->lson->cnt;
            y->cnt -= y->lson->cnt;
        }
        y->lson = x;
        y->cnt += x->cnt;
    }
    return y;
}

Node *right_rotate(Node *y) {
    Node *x = y->lson;
    if (x) {
        y->lson = x->rson;
        y->cnt -= x->cnt;
        if (x->rson) {
            y->cnt += x->rson->cnt;
            x->cnt -= x->rson->cnt;
        }
        x->rson = y;
        x->cnt += y->cnt;
    }
    return x;
}

Node arr[MAX_N];
int arr_cnt = 0;

Node *new_node(int k) {
    arr[arr_cnt] = Node(k, rand());
    return &arr[arr_cnt++];
}

void insert(Node *&root, int key) {
    if (!root) {
        root = new_node(key);
        return;
    }
    if (key <= root->key) {
        insert(root->lson, key);
        root->cnt++;
        if (root->lson->priority > root->priority) {
            root = right_rotate(root);
        }
    } else {
        insert(root->rson, key);
        root->cnt++;
        if (root->rson->priority > root->priority) {
            root = left_rotate(root);
        }
    }
}

int size(Node *root) {
    return root ? root->cnt : 0;
}

int query(Node *root, int k) {
    if (!root) return 0;
    int cnt = size(root->lson) + 1;

    if (cnt == k) {
        return root->key;
    } else if (k < cnt) {
        return query(root->lson, k);
    } else {
        return query(root->rson, k - cnt);
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    int n, m, a[MAX_N], last = 0, cur, k = 1;
    Node *root;
    srand(time(NULL));

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    for (int i = 0; i < m; ++i) {
        scanf("%d", &cur);
        for (int j = last; j < cur; ++j) {
            insert(root, a[j]);
        }
        last = cur;
        printf("%d\n", query(root, k++));
    }

    return 0;
}
