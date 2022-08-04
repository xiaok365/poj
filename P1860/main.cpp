#include <iostream>

using namespace std;

#define MAX_N 101
#define MAX_M 101

template<typename T>
class Cqueue {
public:
    explicit Cqueue(int capacity);

    void Push(T &node);

    T Pop();

    bool IsNotEmpty() {
        return head_ != tail_;
    }

    bool IsEmpty() {
        return head_ == tail_;
    }

    bool IsFull() {
        return (tail_ + 1) % capacity_ == head_;
    }

private:
    int capacity_, head_, tail_;
    T *data_;
};

template<typename T>
Cqueue<T>::Cqueue(int capacity) {
    capacity_ = capacity;
    head_ = tail_ = 0;
    data_ = new T[capacity_];
}

template<typename T>
void Cqueue<T>::Push(T &node) {
    data_[tail_] = node;
    tail_ = (tail_ + 1) % capacity_;
}

template<typename T>
T Cqueue<T>::Pop() {
    T tmp = data_[head_];
    head_ = (head_ + 1) % capacity_;
    return tmp;
}

struct Edge {
    int to, next;
    double r, c;

    Edge() {}

    Edge(int t, int n, double r, double c) : to(t), next(n), r(r), c(c) {}
};

Edge edge[2 * MAX_M];
int edge_cnt = 0, head[MAX_N], n, m, s;
double dist[MAX_N], v;

void add_edge(int from, int to, double r, double c) {
    edge[edge_cnt] = Edge(to, head[from], r, c);
    head[from] = edge_cnt++;
}

void init() {
    // 初值
    memset(head, 0xff, sizeof(head));

    for (int i = 0; i < MAX_N; ++i) {
        dist[i] = -10000;
    }

    // 读入
    scanf("%d %d %d %lf\n", &n, &m, &s, &v);
    for (int i = 0; i < m; ++i) {
        int from, to;
        double r, c;
        scanf("%d %d %lf %lf", &from, &to, &r, &c);
        add_edge(from, to, r, c);
        scanf("%lf %lf", &r, &c);
        add_edge(to, from, r, c);
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    Cqueue<int> my_queue(10000);

    init();
    my_queue.Push(s);
    dist[s] = v;

    // 顶点入队次数
    int v_cnt[MAX_N] = {0};
    v_cnt[s] = 1;

    while (my_queue.IsNotEmpty()) {

        int current = my_queue.Pop();
        if (v_cnt[current] == n) {
            printf("YES\n");
            return 0;
        }

        int edge_i = head[current];
        while (edge_i != -1) {
            if ((dist[current] - edge[edge_i].c) * edge[edge_i].r > dist[edge[edge_i].to]) {
                dist[edge[edge_i].to] = (dist[current] - edge[edge_i].c) * edge[edge_i].r;
                my_queue.Push(edge[edge_i].to);
                v_cnt[edge[edge_i].to]++;
            }
            edge_i = edge[edge_i].next;
        }
    }

    printf("NO\n");

    return 0;
}
