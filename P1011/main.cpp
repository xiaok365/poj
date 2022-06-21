#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <functional>

using namespace std;

int n, a[64];
bool used[64];

bool search(int step, int last, int value, int stick) {

    if (step == n) {
        return value == 0;
    }

    int i = 0;
    if (value != 0) {
        i = last + 1;
    } else {
        int j;
        for (j = 0; j < n; ++j) {
            if (!used[j]) break;
        }
        i = j;
    }
    while (i < n) {
        if (!used[i] && value + a[i] <= stick) {
            used[i] = true;
            bool result = search(step + 1, i, (value + a[i]) % stick, stick);
            used[i] = false;
            if (value == 0 && !result) {
                return false;
            }

            if (value + a[i] == stick && !result) {
                return false;
            }

            if (!result) {
                while (a[i] == a[i + 1]) i++;
            }
            if (result) {
                return true;
            }
        }
        i++;
    }

    return false;
}

int main() {
    ifstream cin("../a.in");
    ofstream cout("../a.out");

    cin >> n;
//    scanf("%d", &n);
    while (n > 0) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
            used[i] = false;
        }

        //降序排序
        sort(a, a + n, greater<int>());

        for (int i = a[0]; i <= sum; ++i) {
            if (sum % i == 0 && search(0, 0, 0, i)) {
                cout << i << endl;
//                printf("%d\n", i);
                break;
            }
        }
        cin >> n;
//        scanf("%d", &n);
    }
    cin.close();
    cout.close();

    return 0;
}