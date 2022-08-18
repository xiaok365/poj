#include <iostream>
#include <cstring>

#define ALPHABET_SIZE 26
#define MAX_N 500000
int order = 0, cnt[MAX_N], father[MAX_N];

struct Node {
    int order_;
    bool is_word_;
    Node *child_[ALPHABET_SIZE];

    Node() : order_(-1), is_word_(false) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) child_[i] = NULL;
    }
};

class Trie {
public:

    int Insert(const char word[], int len);

    bool Find(const char word[], int len);

private:
    Node root;
};

int Trie::Insert(const char word[], int len) {

    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        if (!p->child_[word[i] - 'a']) {
            p->child_[word[i] - 'a'] = new Node;
        }
        p = p->child_[word[i] - 'a'];
    }

    if (!p->is_word_) {
        p->is_word_ = true;
        p->order_ = order++;
    }
    cnt[p->order_]++;
    return p->order_;
}

bool Trie::Find(const char word[], int len) {

    Node *p = &root;
    for (int i = 0; i < len; ++i) {
        if (!p->child_[word[i] - 'a']) {
            return false;
        }
        p = p->child_[word[i] - 'a'];
    }
    return p->is_word_;
}

int find_father(int s) {

    int root = s, temp;
    // 查找s的最顶层根
    while (father[root] >= 0 && father[root] != root) {
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

void union_set(int s, int e) {

    int rootS = find_father(s);
    int rootE = find_father(e);
    if (rootS == rootE) return;

    int weight = father[rootS] + father[rootE];
    // 将结点数少的集合作为结点数多的集合的儿子节点
    if (father[rootS] > father[rootE]) {
        father[rootS] = rootE;
        father[rootE] = weight;
    } else {
        father[rootE] = rootS;
        father[rootS] = weight;
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    Trie my_trie;
    memset(father, 0xff, sizeof father);

    char a[11], b[11];
    while (~scanf("%s %s", a, b)) {
        int i = my_trie.Insert(a, strlen(a));
        int j = my_trie.Insert(b, strlen(b));
        union_set(i, j);
    }

    int odd = 0, f = find_father(0);

//    for (int i = 0; i < order; ++i) {
//        printf("i=%d,father=%d, cnt=%d\n", i, find_father(i), cnt[i]);
//    }

    bool single = true;
    for (int i = 0; i < order; ++i) {
        if ((cnt[i] & 1)) odd++;
        if (f != find_father(i)) {
            single = false;
            break;
        }
    }

//    printf("odd=%d, single=%d\n", odd, single);

    if ((odd == 0 || odd == 2) && single) printf("Possible"); else printf("Impossible");

    return 0;
}
