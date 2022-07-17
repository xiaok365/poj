#include <iostream>
#include <cmath>

using namespace std;

#define N 9
int chessboard[N][N];
int d[2][N][N][N][N];
int sum[N][N] = {0};

int getSum(int x, int y, int k, int l) {
    int ans = sum[k][l] - sum[k][y - 1] - sum[x - 1][l] + sum[x - 1][y - 1];
    return ans * ans;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    int n;
    double average;
    cin >> n;

    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            cin >> chessboard[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + chessboard[i][j];
        }
    }

    // 初始化
    average = sum[N - 1][N - 1] * 1.0 / n;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            for (int k = i; k < N; ++k) {
                for (int l = j; l < N; ++l) {
                    d[0][i][j][k][l] = getSum(i, j, k, l);
                }
            }
        }
    }

    int s = 0;
    for (int t = 1; t < n; ++t) {
        s = 1 - s;
        // 枚举起点
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < N; ++j) {
                // 枚举终点
                for (int k = i; k < N; ++k) {
                    for (int l = j; l < N; ++l) {
                        d[s][i][j][k][l] = 1e8;
                        // 横切
                        for (int a = i; a < k; ++a) {
                            d[s][i][j][k][l] = min(d[s][i][j][k][l], d[1 - s][i][j][a][l] + getSum(a + 1, j, k, l));
                            d[s][i][j][k][l] = min(d[s][i][j][k][l], d[1 - s][a + 1][j][k][l] + getSum(i, j, a, l));
                        }
                        // 纵切
                        for (int b = j; b < l; ++b) {
                            d[s][i][j][k][l] = min(d[s][i][j][k][l], d[1 - s][i][j][k][b] + getSum(i, b + 1, k, l));
                            d[s][i][j][k][l] = min(d[s][i][j][k][l], d[1 - s][i][b + 1][k][l] + getSum(i, j, k, b));
                        }
                    }
                }
            }
        }
    }

    double ans = d[s][1][1][8][8] * 1.0 / n - average * average;
    printf("%.3lf", sqrt(ans));

    return 0;
}
