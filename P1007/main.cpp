#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    string key;
    int value;
};

Node a[100];

int char2int(char c) {
    switch (c) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            return -1;
    }
}

int add(int *a, int key) {

    int total = 0;
    for (int i = 0; i < key; ++i) {
        total += a[i];
    }
    return total;
}

int getUnSorted(string &st) {

    int sum[4] = {0};
    int unsortedness = 0;
    for (long i = st.size() - 1; i >= 0; --i) {
        unsortedness += add(sum, char2int(st[i]));
        sum[char2int(st[i])]++;
    }
    return unsortedness;
}

void swap(Node *a, Node *b) {
    string s;
    int t;
    s = a->key;
    t = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = s;
    b->value = t;

}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> a[i].key;
        a[i].value = getUnSorted(a[i].key);
    }

    for (int i = 0; i < m - 1; ++i)
        for (int j = i + 1; j < m; ++j) {
            if (a[i].value > a[j].value) {
                swap(&a[i], &a[j]);
            }
        }

    for (int i = 0; i < m; ++i) {
        cout << a[i].key << endl;
    }

    return 0;
}