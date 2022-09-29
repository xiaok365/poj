#include <iostream>

#define MAX_N 110
#define MAX_LEN 11
#define MAX_CHILD 4
#define MOD 100000
#define LL long long

struct Node {
    int index;
    Node *fail, *child[MAX_CHILD];

    Node() {
        memset(child, 0, sizeof child);
    }
};

template<typename T>
struct Queue {
    static const int MAX_QUEUE_LEN = 110;
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

struct Matrix {
    LL data[MAX_N][MAX_N];

    Matrix() {
        memset(data, 0, sizeof data);
    }
};

int g_index;
bool virus[MAX_N];
Node *node_ptr[MAX_N];

int to(char ch) {
    switch (ch) {
        case 'A':
            return 0;
        case 'T':
            return 1;
        case 'C':
            return 2;
        default:
            return 3;
    }
}

void insert(Node *root, char st[]) {
    int len = strlen(st);
    for (int i = 0; i < len; ++i) {
        if (!root->child[to(st[i])]) {
            root->child[to(st[i])] = new Node();
            node_ptr[g_index] = root->child[to(st[i])];
            root->child[to(st[i])]->index = g_index++;
        }
        root = root->child[to(st[i])];
    }
    virus[root->index] = true;
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

            if (failure->child[i]) {
                cur->child[i]->fail = failure->child[i];
                virus[cur->child[i]->index] |= virus[failure->child[i]->index];
            } else {
                cur->child[i]->fail = failure;
                virus[cur->child[i]->index] |= virus[failure->index];
            }
            que.push(cur->child[i]);
        }
    }
}

Node *find_next(Node *root, Node *cur, char ch) {
    while (!cur->child[ch] && cur != root) {
        cur = cur->fail;
    }
    if (cur->child[ch]) return cur->child[ch];
    else return cur;
}

Matrix mul(Matrix &s, Matrix &t, int n, int m) {
    Matrix tmp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) tmp.data[i][j] = (tmp.data[i][j] + s.data[i][k] * t.data[k][j]) % m;
    return tmp;
}

Matrix pow_matrix(Matrix &a, int b, int n, int m) {
    Matrix ret;
    for (int i = 0; i < n; i++) {
        ret.data[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            ret = mul(ret, a, n, m);
        }
        a = mul(a, a, n, m);
        b >>= 1;
    }
    return ret;
}

Matrix build_matrix(Node *root) {
    Matrix dist;
    for (int i = 0; i < g_index; ++i) {
        for (int j = 0; j < MAX_CHILD; ++j) {
            if (virus[i]) continue;
            if (!node_ptr[i]->child[j]) {
                Node *next = find_next(root, node_ptr[i], j);
                if (!virus[next->index]) {
                    dist.data[i][next->index]++;
                }
            } else {
                if (!virus[node_ptr[i]->child[j]->index]) {
                    dist.data[i][node_ptr[i]->child[j]->index]++;
                }
            }
        }
    }
    return dist;
}

void init(Node *root, int *n, int *m) {
    memset(virus, false, sizeof virus);
    memset(node_ptr, 0, sizeof node_ptr);

    g_index = 0;
    node_ptr[g_index] = root;
    root->index = g_index++;

    scanf("%d %d", n, m);
    char virus_str[MAX_LEN];
    for (int i = 0; i < *n; ++i) {
        scanf("%s", virus_str);
        insert(root, virus_str);
    }
}

LL solve(Node *root, int m) {

    bfs(root);
    Matrix dist = build_matrix(root);
    Matrix ret = pow_matrix(dist, m, g_index, MOD);

    LL ans = 0;
    for (int i = 0; i < g_index; ++i) ans += ret.data[0][i];

    return ans % MOD;
}

int main() {
    freopen("../a.in", "r", stdin);

    int n, m;
    Node root;

    init(&root, &n, &m);
    printf("%lld", solve(&root, m));

    return 0;
}
