#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 31
#define MAX_SCORE 101

int l1, l2, num1[MAX_N], num2[MAX_N];

bool cmp1(int a, int b) {
    return a > b;
}

bool cmp2(int a, int b) {
    if (a % 10 != b % 10) {
        return a % 10 < b % 10;
    }
    return a < b;
}

void init() {

    int d, n1, n2;
    bool exist[MAX_SCORE];

    scanf("%d %d", &n1, &n2);

    l1 = l2 = 0;
    memset(exist, false, sizeof exist);
    for (int i = 0; i < n1; ++i) {
        scanf("%d", &d);
        if (!exist[d]) {
            num1[l1++] = d;
            exist[d] = true;
        }
    }

    memset(exist, false, sizeof exist);
    for (int i = 0; i < n2; ++i) {
        scanf("%d", &d);
        if (!exist[d]) {
            num2[l2++] = d;
            exist[d] = true;
        }
    }
}

void display(int ans[], int &ans_cnt) {
    if (ans_cnt == 0) {
        printf("NONE");
    } else {
        for (int i = 0; i < ans_cnt; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
        sort(ans, ans + ans_cnt, cmp2);
        for (int i = 0; i < ans_cnt; ++i) {
            printf("%d ", ans[i]);
        }
    }
    printf("\n");
}

int main() {

    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {

        init();

        sort(num1, num1 + l1, cmp1);
        sort(num2, num2 + l2, cmp1);

        int i, j, tmp[MAX_N], tmp_cnt, ans[MAX_N], ans_cnt;
        i = j = tmp_cnt = ans_cnt = 0;

        while (i < l1 && j < l2) {
            if (num1[i] == num2[j]) {
                tmp[tmp_cnt++] = num1[i++];
                j++;
                if (tmp_cnt > ans_cnt) {
                    memcpy(ans, tmp, 4 * tmp_cnt);
                    ans_cnt = tmp_cnt;
                }
            } else if (num1[i] > num2[j]) {
                i++, tmp_cnt = 0;
            } else {
                j++, tmp_cnt = 0;
            }
        }

        display(ans, ans_cnt);
    }

    return 0;
}