#include <iostream>

using namespace std;

const int d[5][2] = {{0,  0},
                     {0,  1},
                     {-1, 0},
                     {0,  -1},
                     {1,  0}};

int origin[4][4] = {0}, map[4][4] = {0};

void flip(int state) {
    int row = state / 4, column = state % 4;

    int dx, dy;
    for (int i = 0; i < 5; ++i) {
        dx = row + d[i][0];
        dy = column + d[i][1];
        if (dx >= 0 && dx < 4 && dy >= 0 && dy < 4) {
            map[dx][dy] ^= 1;
        }
    }
}

bool find() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (map[i][j] != map[0][0]) {
                return false;
            }
        }
    }
    return true;
}

int count_one(int n) {
    int total = 0;
    while (n > 0) {
        total++;
        n &= n - 1;
    }
    return total;
}

int main() {

    freopen("../a.in", "r", stdin);

    char ch[4];
    for (int i = 0; i < 4; ++i) {
        scanf("%s", ch);
        for (int j = 0; j < 4; ++j) {
            if (ch[j] == 'b') {
                origin[i][j] = 1;
            }
        }
    }

    int ans = 17;
    for (int i = 0; i < 65536; ++i) {
        int k = count_one(i);
        if (k >= ans) {
            continue;
        }
        memcpy(map, origin, sizeof(origin));
        for (int j = 0; j < 16; ++j) {
            if (i >> j & 1) {
                flip(j);
            }
        }

        if (find()) {
            ans = k;
        }
    }

    if (ans == 17) {
        cout << "Impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}