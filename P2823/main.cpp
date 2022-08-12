#include <iostream>

using namespace std;

#define N 1000001

struct Node {
    int value, index;
    Node() {}
    Node(int v, int i) : value(v), index(i) {}
};

struct Cqueue {
    Node data[N];
    int head, tail;
    Cqueue() : head(0), tail(0) {}
    bool IsEmpty() { return head == tail; }
    void Push(int x, int i) { data[tail++] = Node(x, i); }
    void Pop() { head++; }
    Node Top() { return data[head]; }
};

Cqueue asc, desc;
int ans[N][2], k;

void binary_search(Cqueue &que, int x, bool asc_order) {
    int l = que.head, r = que.tail - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (asc_order && que.data[mid].value >= x || !asc_order && que.data[mid].value <= x) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (asc_order && que.data[l].value < x || !asc_order && que.data[l].value > x) que.tail = l + 1;
    else que.tail = l;
}

void pop(Cqueue &que, int i) {
    if (!que.IsEmpty() && i - que.Top().index >= k) que.Pop();
}

void push_que(Cqueue &que, int x, int i, bool asc_order) {

    if (que.IsEmpty()) {
        que.Push(x, i);
        return;
    }

    binary_search(que, x, asc_order);
    que.Push(x, i);
    pop(que, i);
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, x;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        if (i < k - 1) {
            push_que(asc, x, i, true);
            push_que(desc, x, i, false);
        } else {
            push_que(asc, x, i, true);
            push_que(desc, x, i, false);
            ans[i - k + 1][0] = asc.Top().value;
            ans[i - k + 1][1] = desc.Top().value;
        }
    }

    // 输出结果
    for (int i = 0; i <= n - k; ++i) { printf("%d ", ans[i][0]); }
    printf("\n");
    for (int i = 0; i <= n - k; ++i) { printf("%d ", ans[i][1]); }

    return 0;
}
