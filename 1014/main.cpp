#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>

using namespace std;

bool dp(const int num[], const int weight) {

    bool f[60001] = {false};

    f[0] = true;
    int m = weight >> 1;

    for (int i = 0; i < 6; ++i) {

        // 二进制优化选择第i个物品
        int present = num[i];

        while (present > 1) {
            int k = 1;
            while (k <= (present >> 1) && (i + 1) * k <= m) {
                int minWeight = (i + 1) * k;
                for (int j = m; j >= minWeight; --j) {
                    int temp = (i + 1) * k;
                    f[j] = f[j] || f[j - temp];
                }
                k <<= 1;
            }
            if (k > 1) {
                present -= k - 1;
            }
        }

        if (present == 1) {
            for (int j = m; j >= i + 1; --j) {
                f[j] = f[j] || f[j - (i + 1)];
            }
        }
    }

    return f[m];
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int sum = 1, index = 0, num[6];

    while (sum > 0) {

        index++;
        sum = 0;
        for (int i = 0; i < 6; ++i) {
            cin >> num[i];
            sum += num[i] * (i + 1);
        }

        if (sum == 0) break;

        cout << "Collection #" << index << ":" << endl;
        if (((sum & 1) == 0) && dp(num, sum)) {
            cout << "Can be divided." << endl << endl;
        } else {
            cout << "Can't be divided." << endl << endl;
        }
    }

    return 0;
}