#include <iostream>

#define MAX_N 11

struct Node {
    int v;
    bool is_word;
    Node *son[2];

    Node() : v(0), is_word(false) {
        memset(son, 0, sizeof son);
    }
};

Node arr[1000];
int cnt = 0;

Node *new_node() {
    return &arr[cnt++];
}

void insert(Node *root, char st[], int order) {
    Node *p = root;
    for (int i = 0; i < strlen(st); ++i) {
        int t = st[i] - '0';
        if (!p->son[t]) {
            p->son[t] = new_node();
        }
        p->son[t]->v = order;
        p = p->son[t];
    }
    p->is_word = true;
}

bool find(Node *root, char st[], int order) {
    Node *p = root;
    for (int i = 0; i < strlen(st); ++i) {
        int t = st[i] - '0';
        if (!p->son[t] || p->son[t]->v != order) {
            return false;
        }
        if (p->son[t]->is_word) return true;
        p = p->son[t];
    }
    return true;
}

int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N], order = 0;

    while (~scanf("%s", st)) {
        Node root;
        order++;
        memset(arr, 0, sizeof arr);

        bool flag = true;
        while (st[0] != '9') {
            if (find(&root, st, order)) {
                flag = false;
            }
            insert(&root, st, order);
            scanf("%s", st);
        }

        if (flag) printf("Set %d is immediately decodable\n", order);
        else printf("Set %d is not immediately decodable\n", order);
    }

    return 0;
}
