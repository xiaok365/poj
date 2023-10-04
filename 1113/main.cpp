#include <iostream>
#include <algorithm>
#include <cmath>

#define MAX_N 1200

template<typename T>
class Deque {
public:
    explicit Deque(int capacity);

    void PushFront(const T &node);

    void PushBack(const T &node);

    T PopFront();

    T PopBack();

    T &Front(int i) { return data_[(head_ + i) % capacity_]; }

    T &Back(int i) { return data_[(tail_ - 1 - i + capacity_) % capacity_]; }

    int Size();

public:
    int capacity_, head_, tail_;
    T *data_;
};

template<typename T>
Deque<T>::Deque(int capacity) {
    capacity_ = capacity;
    head_ = tail_ = 0;
    data_ = new T[capacity_];
}

template<typename T>
void Deque<T>::PushBack(const T &node) {
    data_[tail_] = node;
    tail_ = (tail_ + 1) % capacity_;
}

template<typename T>
void Deque<T>::PushFront(const T &node) {
    head_ = (head_ - 1 + capacity_) % capacity_;
    data_[head_] = node;
}

template<typename T>
T Deque<T>::PopBack() {
    tail_ = (tail_ - 1 + capacity_) % capacity_;
    return data_[tail_];
}

template<typename T>
T Deque<T>::PopFront() {
    head_ = (head_ + 1) % capacity_;
    return data_[(head_ - 1 + capacity_) % capacity_];
}

template<typename T>
int Deque<T>::Size() {
    if (head_ <= tail_) {
        return tail_ - head_;
    } else {
        return tail_ + (capacity_ - head_);
    }
}

struct Node {
    int x, y;
};

const double pi = acos(-1.0);

Node node[MAX_N];
int n, l;
Deque<Node> deque(MAX_N);

bool cmp(const Node &a, const Node &b) {
    if (a.y == b.y)return a.x < b.x;
    return a.y < b.y;
}

int cross(Node &a, Node &b, Node &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dis(Node &a, Node &b) {
    return sqrt(pow(double(b.x - a.x), 2) + pow(double(b.y - a.y), 2));
}

double melkman() {

    deque.PushBack(node[0]);

    // 跳过共线
    int k = 2;
    for (; k < n; ++k) {
        if (cross(node[0], node[k - 1], node[k]) != 0) break;
    }

    if (cross(node[0], node[k - 1], node[k]) > 0) {
        deque.PushBack(node[k - 1]);
    } else {
        deque.PushFront(node[k - 1]);
    }

    deque.PushFront(node[k]);
    deque.PushBack(node[k]);

    for (int i = k + 1; i < n; ++i) {
        if (cross(deque.Back(1), deque.Back(0), node[i]) > 0 &&
            cross(deque.Front(0), deque.Front(1), node[i]) > 0) {
            continue;
        }

        while (cross(deque.Front(0), deque.Front(1), node[i]) <= 0) {
            deque.PopFront();
        }
        deque.PushFront(node[i]);

        while (cross(deque.Back(1), deque.Back(0), node[i]) <= 0) {
            deque.PopBack();
        }
        deque.PushBack(node[i]);
    }

    double ans = 0;
    while (deque.Size() > 1) {
        ans += dis(deque.Front(0), deque.Front(1));
//        printf("%d %d\n", deque.Front(0).x, deque.Front(0).y);
        deque.PopFront();
    }
//    printf("%d %d\n", deque.Front(0).x, deque.Front(0).y);

    ans += 2 * pi * l;

    return ans;
}

int main() {
    freopen("../a.in", "r", stdin);

    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; ++i) scanf("%d %d", &node[i].x, &node[i].y);

//    std::sort(node, node + n, cmp);

    printf("%.0lf", melkman());

    return 0;
}
