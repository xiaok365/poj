#include <iostream>

using namespace std;

#define MAX_N 1001
#define MAX_CHILD 26

struct Node {
    int index;
    bool is_word;
    Node *fail, *child[MAX_CHILD];

    Node() : index(0), is_word(false) {
        memset(child, 0, sizeof child);
    }
};

template<typename T>
struct Queue {
    static const int MAX_QUEUE_LEN = 500010;
    int head, tail;
    T data[MAX_QUEUE_LEN];

    Queue() : head(0), tail(0) { memset(data, 0, sizeof data); }

    bool is_not_empty() { return head != tail; }

    void push(T t) {
        data[tail] = t;
        tail = (tail + 1) % MAX_QUEUE_LEN;
    }

    T pop() {
        head = (head + 1) % MAX_QUEUE_LEN;
        return data[(head - 1 + MAX_QUEUE_LEN) % MAX_QUEUE_LEN];
    }
};

const int dir[8][2] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};
char dir_ch[9] = "ABCDEFGH";
char puzzle[MAX_N][MAX_N];
int n, m, w, ans[MAX_N][3];

void insert(Node *root, char st[], int idx) {
    int len = strlen(st);
    for (int i = len - 1; i >= 0; --i) {
        if (!root->child[st[i] - 'A']) {
            root->child[st[i] - 'A'] = new Node();
        }
        root = root->child[st[i] - 'A'];
    }
    root->is_word = true;
    root->index = idx;
}

void bfs(Node *root) {
    Queue<Node *> que;
    for (int i = 0; i < MAX_CHILD; ++i) {
        if (root->child[i]) {
            root->child[i]->fail = root;
            que.push(root->child[i]);
        }
    }

    while (que.is_not_empty()) {
        Node *cur = que.pop();
        for (int i = 0; i < MAX_CHILD; ++i) {
            if (!cur->child[i]) continue;
            Node *failure = cur->fail;
            while (!failure->child[i] && failure != root) failure = failure->fail;
            if (failure->child[i]) cur->child[i]->fail = failure->child[i];
            else cur->child[i]->fail = failure;
            que.push(cur->child[i]);
        }
    }
}

Node *find_next(Node *root, Node *cur, char ch) {
    ch = ch - 'A';
    while (!cur->child[ch] && cur != root) {
        cur = cur->fail;
    }
    if (cur->child[ch]) return cur->child[ch];
    else return cur;
}

void traverse(Node *root, int x, int y, int d) {
    Node *cur = root;
    while (x >= 0 && x < n && y >= 0 && y < m) {
        cur = find_next(root, cur, puzzle[x][y]);
        Node *tmp = cur;
        while (tmp != root) {
            if (tmp->is_word) {
                ans[tmp->index][0] = x;
                ans[tmp->index][1] = y;
                ans[tmp->index][2] = (d + 4) % 8;
            }
            tmp = tmp->fail;
        }
        x += dir[d][0];
        y += dir[d][1];
    }
}

void solve(Node *root) {
    bfs(root);
    // 行
    for (int i = 0; i < n; ++i) {
        traverse(root, i, 0, 2), traverse(root, i, m - 1, 6);
        traverse(root, i, 0, 3), traverse(root, i, m - 1, 5);
        traverse(root, i, 0, 1), traverse(root, i, m - 1, 7);
    }
    // 列
    for (int j = 0; j < m; ++j) {
        traverse(root, 0, j, 4), traverse(root, n - 1, j, 0);
        traverse(root, 0, j, 3), traverse(root, n - 1, j, 1);
        traverse(root, 0, j, 5), traverse(root, n - 1, j, 7);
    }
    for (int i = 0; i < w; ++i) {
        printf("%d %d %c\n", ans[i][0], ans[i][1], dir_ch[ans[i][2]]);
    }
}

void init(Node *root) {
    scanf("%d %d %d", &n, &m, &w);
    for (int i = 0; i < n; ++i) {
        scanf("%s", puzzle[i]);
    }
    char word[MAX_N];
    for (int i = 0; i < w; ++i) {
        scanf("%s", word);
        insert(root, word, i);
    }
}

int main() {

    freopen("../a.in", "r", stdin);
    Node root;
    init(&root);
    solve(&root);

    return 0;
}
