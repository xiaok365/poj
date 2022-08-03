#include <iostream>

using namespace std;
enum Type {
    MAX_HEAP, //大根堆
    MIN_HEAP //小根堆
};

template<typename T>
struct Node {
    T value;

    Node() {}

    Node(T v) : value(v) {
    }

    Node(const Node &from) {
        value = from.value;
    }

};

template<typename T>
class Heap {
public:

    Heap(int capacity, Type type) : capacity_(capacity), type_(type) {
        data_ = new Node<T>[capacity_];
//        memset(data_, 0, sizeof(T) * capacity_);
        size_ = 0;
    }

    void BuildHeap(T source[], int n);

    void Push(T t);

    Node<T> *Pop();

    int Size() {
        return size_;
    }

    bool IsEmpty() {
        return size_ <= 0;
    }

    bool IsNotEmpty() {
        return size_ > 0;
    }

    void HeapSort();

    T Get(int k);

private:

    Node<T> *data_;
    int capacity_;
    int size_;
    Type type_;

    void HeapUp(int k);

    void HeapDown(int k, int n);

    void Swap(int a, int b);

    bool IsMax() {
        return type_ == MAX_HEAP;
    }

    bool IsMin() {
        return type_ == MIN_HEAP;
    }

    int Compare(Node<T> &a, Node<T> &b);
};

template<typename T>
void Heap<T>::Push(T t) {
    if (size_ >= capacity_) {
        printf("heap is full,capacity_=%d", capacity_);
        return;
    }
    Node<T> node(t);
    data_[size_++] = node;
    HeapUp(size_ - 1);
}

template<typename T>
Node<T> *Heap<T>::Pop() {
    if (size_ <= 0) {
        printf("heap is empty");
        return NULL;
    }
    Node<T> ret = data_[0];
    data_[0] = data_[--size_];
    HeapDown(0, size_ - 1);
    return &ret;
}

template<typename T>
void Heap<T>::HeapUp(int k) {
    int parent, son;
    Node<T> x = data_[k];
    son = k;
    parent = (son - 1) / 2;

    while (son > 0) {
        //如果父结点大于等于heap[k]则退出，否则将父结点下移
        if (IsMax() && Compare(data_[parent], x) >= 0
            || IsMin() && Compare(data_[parent], x) <= 0)
            break;
        data_[son] = data_[parent];
        son = parent;
        parent = (son - 1) / 2;
    }
    data_[son] = x;
}

template<typename T>
void Heap<T>::HeapDown(int k, int n) {
    int parent, son;
    Node<T> x = data_[k];
    parent = k;
    son = 2 * k + 1;    //左孩子结点

    while (son <= n) {
        //比较左右儿子，选择较大的一个
        if (son + 1 <= n &&
            (IsMax() && Compare(data_[son + 1], data_[son]) > 0
             || IsMin() && Compare(data_[son + 1], data_[son]) < 0))
            son++;    //使son指向左右孩子中较大的结点。

        //如果儿子结点中较大的都小于等于待调整结点则退出，否则将子结点上移
        if (IsMax() && Compare(data_[son], x) <= 0 || IsMin() && Compare(data_[son], x) >= 0)
            break;
        data_[parent] = data_[son];
        parent = son;
        son = 2 * parent + 1;
    }
    data_[parent] = x;
}

template<typename T>
void Heap<T>::BuildHeap(T source[], int n) {

    size_ = n;
//    memcpy(data_, source, sizeof(T) * size_);

    for (int i = 0; i < n; ++i) {
        Node<T> node(source[i]);
        data_[i] = node;
    }

    for (int i = (size_ - 2) / 2; i >= 0; --i) {
        HeapDown(i, size_ - 1);
    }
}

template<typename T>
void Heap<T>::Swap(int a, int b) {
    Node<T> temp;
    temp = data_[a];
    data_[a] = data_[b];
    data_[b] = temp;
}

template<typename T>
void Heap<T>::HeapSort() {
    for (int i = size_ - 1; i > 0; --i) {
        Swap(0, i);
        HeapDown(0, i - 1);
    }
}

template<typename T>
T Heap<T>::Get(int k) {
    return data_[k].value;
}

template<typename T>
int Heap<T>::Compare(Node<T> &a, Node<T> &b) {
    if (a.value > b.value)return 1;
    if (a.value < b.value)return -1;

    return 0;
}

int main() {

    freopen("../a.in", "r", stdin);

    Heap<long long> myHeap(20000, MIN_HEAP);

    int n, t;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        myHeap.Push(t);
    }

    long long ans = 0;
    while (myHeap.Size() > 1) {
        long long a = myHeap.Pop()->value;
        long long b = myHeap.Pop()->value;
        ans += a + b;
        myHeap.Push(a + b);
    }

    printf("%lld", ans);

    return 0;
}
