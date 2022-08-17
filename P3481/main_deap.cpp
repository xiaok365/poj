#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node {
    int k, p;

    Node() {}

    Node(int k, int p) : k(k), p(p) {}

    bool operator<(const Node &other) const {
        return p < other.p;
    }

    bool operator>(const Node &other) const {
        return p > other.p;
    }
};

template<typename T>
class Deap {
public:
    explicit Deap(int capacity);

    void Insert(T t);

    T PopMin();

    T PopMax();

    T Min() { return data_[1]; }

    T Max() { return data_[2]; }

    int Size() { return size_; }

    bool IsEmpty() { return size_ == 0; }

public:
    T *data_;
    int capacity_, size_;

    void HeapUp(int k);

    void HeapDownMin(int k);

    void HeapDownMax(int k);

    bool IsRight(int u);

};

template<typename T>
Deap<T>::Deap(int capacity) {
    capacity_ = capacity + 1;
    data_ = new T[capacity_];
    size_ = 0;
}

template<typename T>
void Deap<T>::Insert(T t) {
    if (size_ >= capacity_) {
        printf("heap is full,capacity_=%d", capacity_);
        return;
    }
    data_[++size_] = t;
    HeapUp(size_);
}

template<typename T>
T Deap<T>::PopMin() {
    T ret = data_[1];
    data_[1] = data_[size_--];
    HeapDownMin(1);
    return ret;
}

template<typename T>
T Deap<T>::PopMax() {
    T ret = data_[2];
    if (size_ == 1) {
        ret = data_[1];
        size_ = 0;
        return ret;
    }
    data_[2] = data_[size_--];
    HeapDownMax(2);
    return ret;
}

template<typename T>
bool Deap<T>::IsRight(int u) {
    return (u & 1) == 0;
}


template<typename T>
void Deap<T>::HeapUp(int k) {
    int cur = k;
    T x = data_[k];

    while (cur > 0) {

        // cur在右边
        if (IsRight(cur) && x < data_[cur - 1]) {
            data_[cur] = data_[cur - 1];
            cur--;
        }

        int parent = (cur - 1) >> 1;
        int grand_parent = (parent - 1) >> 1;
        if (grand_parent == -1) break;

        int parent_min = (grand_parent << 1) + 1;
        int parent_max = parent_min + 1;

        if (x < data_[parent_min]) {
            data_[cur] = data_[parent_min];
            cur = parent_min;
        } else if (x > data_[parent_max]) {
            data_[cur] = data_[parent_max];
            cur = parent_max;
        } else break;
    }
    data_[cur] = x;
}

template<typename T>
void Deap<T>::HeapDownMin(int k) {

    int cur = k;
    T x = data_[k];

    while (cur < size_) {
        if (x > data_[cur + 1]) {
            T tmp = data_[cur + 1];
            data_[cur + 1] = x;
            x = tmp;
        }
        int son = (cur << 1) + 1;
        if (son > size_) break;

        if (son + 2 <= size_ && data_[son + 2] < data_[son]) son += 2;

        if (x > data_[son]) {
            data_[cur] = data_[son];
            cur = son;
        } else break;
    }
    data_[cur] = x;
}


template<typename T>
void Deap<T>::HeapDownMax(int k) {

    int cur = k;
    T x = data_[k];

    while (cur <= size_) {
        if (x < data_[cur - 1]) {
            T tmp = data_[cur - 1];
            data_[cur - 1] = x;
            x = tmp;
        }
        int son = cur << 1;
        if (son > size_) break;

        if (son + 2 <= size_ && data_[son + 2] > data_[son]) son += 2;

        if (x < data_[son]) {
            data_[cur] = data_[son];
            cur = son;
        } else break;
    }
    data_[cur] = x;
}

int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    int code, k, p;
    Node node;

    Deap<Node> deap(1000001);
    scanf("%d", &code);
    while (code) {

        switch (code) {
            case 1:
                scanf("%d%d", &k, &p);
                deap.Insert(Node(k, p));
                break;
            case 2:
                if (deap.IsEmpty()) {
                    printf("0\n");
                } else {
                    node = deap.PopMax();
                    printf("%d\n", node.k);
                }
                break;
            case 3:
                if (deap.IsEmpty()) {
                    printf("0\n");
                } else {
                    node = deap.PopMin();
                    printf("%d\n", node.k);
                }
                break;
            default:
                break;
        }
        scanf("%d", &code);
    }

    return 0;
}
