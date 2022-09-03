#include <iostream>

#define ALPHABET_SIZE 26
#define MAX_N 100001
#define MAX_LEN 11

struct Node {
    int order;
    bool is_word;
    Node *child[ALPHABET_SIZE];

    Node() : is_word(false) {
        memset(child, 0, sizeof child);
    }
};

Node root;
char map[MAX_N][MAX_LEN];
int cnt = 0;

void insert(const char key[], const char value[]) {

    int len = strlen(key);
    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        int j = key[i] - 'a';
        if (!p->child[j]) {
            p->child[j] = new Node;
        }
        p = p->child[j];
    }

    p->is_word = true;
    strcpy(map[cnt], value);
    p->order = cnt++;
}

int find(const char key[]) {

    int len = strlen(key);
    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        int j = key[i] - 'a';
        if (!p->child[j]) {
            return -1;
        }
        p = p->child[j];
    }

    if (p->is_word) return p->order; else return -1;
}

int main() {

    freopen("../a.in", "r", stdin);

    char a[MAX_LEN * 2], b[MAX_LEN], c[MAX_LEN];

    while (scanf("%[^\n]", a) && getchar()) {
        sscanf(a, "%s %s", b, c);
        insert(c, b);
    }

    while (~scanf(" %s", a)) {
        int k = find(a);
        if (k != -1) printf("%s\n", map[k]); else printf("eh\n");
    }

    return 0;
}
