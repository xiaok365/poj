#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_N 100005
#define MAX_CHAR 28

struct SuffixNode {
    int start, *end;
    SuffixNode *child[MAX_CHAR];
    SuffixNode *suffix_link;

    SuffixNode() : start(-1), end(NULL), suffix_link(NULL) {
        memset(child, 0, sizeof child);
    }

    int len() const { return *end - start + 1; }
};

SuffixNode node[MAX_N * 10], *root, *last_node, *active_node;
int node_cnt = 0, active_edge = -1, active_length = 0, remaining = 0, leaf_end = -1, len1 = 0;

SuffixNode *new_node(int s, int *e, SuffixNode *link) {
    node[node_cnt].start = s;
    node[node_cnt].end = e;
    node[node_cnt].suffix_link = link;
    return &node[node_cnt++];
}

// 字符离散
int to(char ch) {
    switch (ch) {
        case '#':
            return 26;
        case '$':
            return 27;
        default:
            return ch - 'a';
    }
}

// 向下移动
bool walk_down(const char text[], SuffixNode *cur, int pos) {
    if (active_length >= cur->len()) {
        int edge = pos - active_length + cur->len();
        active_edge = to(text[edge]);
        active_length -= cur->len();
        active_node = cur;
        return true;
    }
    return false;
}

//新增后缀
void insert_ukkonen(const char text[], int pos) {
    leaf_end = pos;
    remaining++;
    last_node = NULL;
    while (remaining) {
        // 无待插入点
        if (active_length == 0) active_edge = to(text[pos]);
        // 无边，新创建
        if (active_node->child[active_edge] == NULL) {
            active_node->child[active_edge] = new_node(pos, &leaf_end, NULL);
            if (last_node != NULL) {
                last_node->suffix_link = active_node;
                last_node = NULL;
            }
        } else {  // 有边
            SuffixNode *next = active_node->child[active_edge];
            // 滑到下一个点
            if (walk_down(text, next, pos)) continue;
            // 延伸
            if (text[next->start + active_length] == text[pos]) {
                if (last_node != NULL && active_node != root) {
                    last_node->suffix_link = active_node;
                    last_node = NULL;
                }
                active_length++;
                break;
            }
            // 新建内部点
            int *splitEnd = new int;
            *splitEnd = next->start + active_length - 1;
            SuffixNode *split = new_node(next->start, splitEnd, root);
            active_node->child[active_edge] = split;
            // 末尾新点
            split->child[to(text[pos])] = new_node(pos, &leaf_end, NULL);
            next->start += active_length;
            // 原点下移
            split->child[to(text[next->start])] = next;
            if (last_node != NULL) {
                last_node->suffix_link = split;
            }
            last_node = split;
        }
        remaining--;
        if (active_node == root && active_length > 0) {
            active_length--;
            active_edge = to(text[pos - remaining + 1]);
        } else if (active_node != root) {
            active_node = active_node->suffix_link;
        }
    }
}

// 建树
void build(char st[]) {
    int *root_end = new int;
    *root_end = -2;
    root = new_node(-1, root_end, NULL);
    active_node = root;
    int len = strlen(st);
    for (int i = 0; i < len; ++i) {
        insert_ukkonen(st, i);
    }
}

// 查找子树包含#和不含#的结点最大深度，即最长公共子串
int find(char c[], SuffixNode *p, int depth, int &ans) {
    int t = 0;
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (p->child[i]) {
            t |= find(c, p->child[i], depth + p->child[i]->len(), ans);
        }
    }
    if (t == 0) {
        if (*p->end >= len1 && p->start <= len1) {
            return 1;
        }
        return 2;
    }
    if (t == 3) ans = max(ans, depth);
    return t;
}

struct StNode {
    char v[1000];

    bool operator<(const StNode &other) const {
        return strlen(v) < strlen(other.v);
    }
} arr[1000];

int cnt = 0;

// 遍历后缀
void traverse(SuffixNode *p, char text[], char dst[]) {
    bool leaf = true;
    char t[MAX_N] = "";
    strncpy(t, text + p->start, p->len());
    char t1[MAX_N] = "";
    sprintf(t1, "%s%s", dst, t);
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (p->child[i]) {
            leaf = false;
            traverse(p->child[i], text, t1);
        }
    }
    if (leaf) strcpy(arr[cnt++].v, t1);
}

int main() {
    freopen("../a.in", "r", stdin);

    char a[MAX_N], b[MAX_N], c[MAX_N * 2];
    scanf("%s %s", a, b);
    len1 = strlen(a);
    sprintf(c, "%s#%s$", a, b);
    build(c);

    int ans = 0;
    find(c, root, 0, ans);
    printf("%d\n", ans);

    // 输出全部后缀
    traverse(root, c, "");
    sort(arr, arr + cnt);
    for (int i = 0; i < cnt; ++i) {
        printf("%d %s\n", (int) strlen(arr[i].v), arr[i].v);
    }

    return 0;
}