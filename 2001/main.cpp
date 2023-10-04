#include <iostream>
#include <cstring>

#define  ALPHABET_SIZE 26
#define  MAX_N 1001

struct Node {
    int cnt;
    bool is_word_;
    Node *child_[ALPHABET_SIZE];

    Node() : cnt(0), is_word_(false) {
        memset(child_, 0, sizeof child_);
    }
};

Node root;
char word[MAX_N][21];

void insert(int index, int len) {

    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        int j = word[index][i] - 'a';
        if (!p->child_[j]) {
            p->child_[j] = new Node;
        }
        p->child_[j]->cnt++;
        p = p->child_[j];
    }

    return;
}

int find(int index, int len) {

    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        int j = word[index][i] - 'a';
        if (p->child_[j]->cnt == 1) {
            return i + 1;
        }
        p = p->child_[j];
    }
    return len;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n = 0;

    while (~scanf("%s", word[n])) {
        insert(n, strlen(word[n]));
        n++;
    }

    for (int i = 0; i < n; ++i) {
        int pos = find(i, strlen(word[i]));

        char dest[21] = {0};
        strncpy(dest, word[i], pos);

        printf("%s %s\n", word[i], dest);
    }
    return 0;
}
