#include <iostream>

using namespace std;

// 第i行全为1
const int row_state[4] = {15, 240, 3840, 61440};
// 第j列全为1
const int column_state[4] = {4369, 8738, 17476, 34952};

void flip(int &current, int pos) {
    int row = pos / 4, column = pos % 4;
    current ^= row_state[row];
    current ^= column_state[column];
    current ^= (1 << pos);
}

int count_one(int n) {
    int total = 0;
    while (n > 0) {
        total++;
        n &= n - 1;
    }
    return total;
}

// 打印状态
void display(int state) {
    char a[4][4];
    for (int i = 3; i >= 0; --i) {
        for (int j = 3; j >= 0; --j) {
            if (state & 1) {
                a[i][j] = '-';
            } else {
                a[i][j] = '+';
            }
            state >>= 1;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << a[i][j];
        }
        cout << endl;
    }
}


int main() {

    freopen("../a.in", "r", stdin);

    char ch[4];
    int state = 0;
    for (int i = 0; i < 4; ++i) {
        scanf("%s", ch);
        for (int j = 0; j < 4; ++j) {
            if (ch[j] == '-') {
                state += 1;
            }
            state <<= 1;
        }
    }
    state >>= 1;

    int ans = 17, plan;
    for (int i = 0; i < 65536; ++i) {
        int k = count_one(i);
        if (k >= ans) {
            continue;
        }

        int current = state;
        // 枚举bit位为1的进行翻转
        for (int j = 0; j < 16; ++j) {
            if (i >> j & 1) {
                flip(current, j);
            }
        }

        if (current == 65535) {
            ans = k;
            plan = i;
        }
    }

    printf("%d\n", ans);
    int t = 1 << 15;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (plan & t) {
                printf("%d %d\n", i, j);
            }
            t >>= 1;
        }
    }

    return 0;
}