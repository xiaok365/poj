#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
int charMap[256];

void initCharMap() {
    memset(charMap, 0xff, 256 * sizeof(int));
    charMap['0'] = 0;
    charMap['1'] = 1;
    charMap['A'] = charMap['B'] = charMap['C'] = charMap['2'] = 2;
    charMap['D'] = charMap['E'] = charMap['F'] = charMap['3'] = 3;
    charMap['G'] = charMap['H'] = charMap['I'] = charMap['4'] = 4;
    charMap['J'] = charMap['K'] = charMap['L'] = charMap['5'] = 5;
    charMap['M'] = charMap['N'] = charMap['O'] = charMap['6'] = 6;
    charMap['P'] = charMap['R'] = charMap['S'] = charMap['7'] = 7;
    charMap['T'] = charMap['U'] = charMap['V'] = charMap['8'] = 8;
    charMap['W'] = charMap['X'] = charMap['Y'] = charMap['9'] = 9;
}

int dealStr2Int(string st) {
    int data = 0, bit = 1000000, digit = 0;
    for (int i = 0; i < st.size(); ++i) {
        data = charMap[st[i]];
        if (data < 0)continue;
        digit += data * bit;
        bit /= 10;
    }
    return digit;
}

int heapUp(int *heap, int tail, int num) {
    int i, j;

    heap[tail] = num;//num插入堆尾
    i = tail;
    j = (i - 1) / 2;//j指向i的父结点

    while (i > 0) {
        //如果父亲结点大于插入的结点则退出，否则将父亲结点下移
        if (heap[j] >= num)
            break;
        heap[i] = heap[j];
        i = j;
        j = (i - 1) / 2;
    }

    heap[i] = num;
    return 0;
}

int heapDown(int *heap, int top, int n) {
    int j = 2 * top + 1;    //左孩子结点
    int x = heap[top];

    while (j <= n) {
        //比较左右儿子，选择较小的一个
        if (j + 1 <= n && heap[j + 1] > heap[j])
            j++;    //使j指向左右孩子中较小的结点。

        //如果儿子结点中较大的都小于插入的结点则退出
        if (heap[j] <= x)
            break;
        heap[top] = heap[j];
        top = j;
        j = 2 * top + 1;
    }
    heap[top] = x;
    return 0;
}

void swap(int &a, int &b) {
    a ^= b ^= a ^= b;
}

void heapSort(int *heap, int tail) {
    for (int i = tail - 1; i > 0; --i) {
        swap(heap[0], heap[i]);
        heapDown(heap, 0, i - 1);
    }
}

string int2str(int data) {
    stringstream stream;
    stream << data;
    return stream.str();
}

string getZeroStr(long n) {
    string st;
    for (int i = 0; i < n; ++i) st += '0';
    return st;
}

string processTel(int data) {

    string first, second;
    first = int2str(data / 10000);
    first = getZeroStr(3 - first.size()) + first;
    second = int2str(data % 10000);
    second = getZeroStr(4 - second.size()) + second;

    return first + '-' + second;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, heap[100000], total = 0;
    string st;

    initCharMap();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> st;
        int data = dealStr2Int(st);
        heapUp(heap, total++, data);
    }
    heapSort(heap, total);
    int j = 0;
    bool duplicate = true;
    while (j < total) {
        int start = j, cur = heap[j];
        while (j + 1 < total && heap[j + 1] == cur) ++j;

        if (j - start > 0) {
            duplicate = false;
            cout << processTel(heap[start]) << " " << j - start + 1 << endl;
        }
        ++j;
    }

    if (duplicate)cout << "No duplicates. " << endl;

    cin.close();
    cout.close();
    return 0;
}