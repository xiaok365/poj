#include <iostream>

#define MAX_N 61

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

Matrix mul(Matrix &s, Matrix &t, int n, int m) {
    Matrix tmp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) tmp.data[i][j] = (tmp.data[i][j] + s.data[i][k] * t.data[k][j]) % m;
    return tmp;
}

Matrix pow_matrix(Matrix &a, int b, int n, int m) {
    Matrix ret;
    for (int i = 0; i < n; i++) {
        ret.data[i][i] = 1;
    }

    while (b) {
        if (b & 1) {
            ret = mul(ret, a, n, m);
        }
        a = mul(a, a, n, m);
        b >>= 1;
    }

    return ret;
}

void display(Matrix &x, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", x.data[i][j]);
        }
        printf("\n");
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, k, m, a[MAX_N][MAX_N] = {0};
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
            a[i][j + n] = a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) a[i + n][i + n] = 1;

    Matrix A(a);
    Matrix B = pow_matrix(A, k, n * 2, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", B.data[i][j + n]);
        }
        printf("\n");
    }

    return 0;
}
