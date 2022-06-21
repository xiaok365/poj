#include <iostream>
#include <fstream>

using namespace std;

int f[21][21][21];

int solve(int a, int b, int c) {

    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }

    if (a > 20 || b > 20 || c > 20) {
        return solve(20, 20, 20);
    }

    if (f[a][b][c] != -1) return f[a][b][c];

    if (a < b && b < c) {
        return f[a][b][c] = solve(a, b, c - 1) + solve(a, b - 1, c - 1) - solve(a, b - 1, c);
    }

    return f[a][b][c] = solve(a - 1, b, c) + solve(a - 1, b - 1, c)
                        + solve(a - 1, b, c - 1) - solve(a - 1, b - 1, c - 1);
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a, b, c;

    while (cin >> a >> b >> c && !(a == -1 && b == -1 && c == -1)) {
        memset(f, 0xff, 21 * 21 * 21 * 4);
        printf("w(%d, %d, %d) = %d\n", a, b, c, solve(a, b, c));
//        cout << solve(a, b, c) << endl;
    }
    return 0;
}