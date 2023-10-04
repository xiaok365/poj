#include <iostream>

using namespace std;

#define MAXN 901

struct Node {
    int to, next;

    Node() : to(0), next(-1) {}

    Node(int to, int next) : to(to), next(next) {}
};

Node son[MAXN];
int query[MAXN][MAXN], son_cnt, son_head[MAXN], father[MAXN], ans[MAXN], in_degree[MAXN];
bool visit[MAXN];

void addSon(int from, int to) {
    son[son_cnt] = Node(to, son_head[from]);
    son_head[from] = son_cnt++;
    in_degree[to]++;
}

void addQuery(int from, int to) {
    query[from][++query[from][0]] = to;
    query[to][++query[to][0]] = from;
}

int find_root(int n) {
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            return i;
        }
    }
    return 0;
}

int find_father(int x) {
    int root = x, t;
    while (father[root] != -1) {
        root = father[root];
    }
    // 压缩路径
    while (x != root) {
        t = father[x];
        father[x] = root;
        x = t;
    }
    return root;
}

void tarjan(int root) {
    visit[root] = true;

    // 关联的查询
    for (int i = 1; i <= query[root][0]; ++i) {
        if (visit[query[root][i]]) {
            int fa = find_father(query[root][i]);
            ans[fa]++;
        }
    }

    // 遍历了结点
    int son_i = son_head[root];
    while (~son_i) {
        tarjan(son[son_i].to);
        father[son[son_i].to] = root;
        son_i = son[son_i].next;
    }
}

void init() {
    son_cnt = 0;
    memset(father, 0xff, sizeof(father));
    memset(son_head, 0xff, sizeof(son_head));
    memset(query, 0, sizeof(query));
    memset(ans, 0, sizeof(ans));
    memset(in_degree, 0, sizeof(in_degree));
    memset(visit, false, sizeof(visit));
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, son_n, m, from, to;
    while (~scanf("%d", &n)) {
        init();
        // 读取n个点
        for (int i = 0; i < n; ++i) {
            scanf("%d", &from);
            while (getchar() != '(');
            scanf("%d", &son_n);
            while (getchar() != ')');
            for (int j = 0; j < son_n; ++j) {
                scanf("%d", &to);
                addSon(from, to);
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            while (getchar() != '(');
            scanf("%d %d", &from, &to);
            while (getchar() != ')');
            addQuery(from, to);
        }

        tarjan(find_root(n));
        // 输出结果
        for (int i = 1; i <= n; ++i) {
            if (ans[i] > 0) {
                printf("%d:%d\n", i, ans[i]);
            }
        }

    }

    return 0;
}
