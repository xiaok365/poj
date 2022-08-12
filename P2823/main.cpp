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

int binary_search(Cqueue &que, int x, bool asc_order) {
    int l = que.head, r = que.tail - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (asc_order && que.data[mid].value >= x || !asc_order && que.data[mid].value <= x) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l + 1;
}

void pop(Cqueue &que, int i) {
    if (!que.IsEmpty() && i - que.Top().index >= k) que.Pop();
}

// 上升队列
void push_asc(int x, int i) {

    if (asc.IsEmpty()) {
        asc.Push(x, i);
        return;
    }

    asc.tail = binary_search(asc, x, true);

    while (!asc.IsEmpty() && asc.data[asc.tail - 1].value >= x) asc.tail--;
    asc.Push(x, i);

    pop(asc, i);
}

// 下降队列
void push_desc(int x, int i) {
    if (desc.IsEmpty()) {
        desc.Push(x, i);
        return;
    }

    desc.tail = binary_search(desc, x, false);

    while (!desc.IsEmpty() && desc.data[desc.tail - 1].value <= x) desc.tail--;
    desc.Push(x, i);

    pop(desc, i);
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, x;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        if (i < k - 1) {
            push_asc(x, i);
            push_desc(x, i);
        } else {
            push_asc(x, i);
            push_desc(x, i);
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
