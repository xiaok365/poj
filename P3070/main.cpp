#include <iostream>

using namespace std;

#define MAX_N 2

struct Matrix {
    int data[MAX_N][MAX_N];
    Matrix() {
        memset(data, 0, sizeof data);
    }
    Matrix(int a[][MAX_N]) {
        for (int i = 0; i < MAX_N; ++i)
            for (int j = 0; j < MAX_N; ++j) data[i][j] = a[i][j];
    }
};

void multi_matrix(Matrix &a, Matrix &b) {
    int i, j;
    Matrix tmp;

    for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_N; j++)
            for (int k = 0; k < MAX_N; k++) {
                tmp.data[i][j] += a.data[i][k] * b.data[k][j];
            }

    for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_N; j++) {
            a.data[i][j] = tmp.data[i][j] % 10000;
        }
}

void pow_matrix(Matrix &a, int b, Matrix &ret) {

    for (int i = 0; i < MAX_N; i++) {
        ret.data[i][i] = 1;
    }

    while (b) {
        if (b & 1) {
            multi_matrix(ret, a);
        }
        multi_matrix(a, a);
        b >>= 1;
    }
}

void display(Matrix &x) {
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            cout << x.data[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, initial[2][2] = {1, 1, 1, 0};

    while (cin >> n && n != -1) {
        Matrix start(initial), ret;
        pow_matrix(start, n, ret);
        cout << ret.data[1][0] << endl;
    }
    return 0;
}
