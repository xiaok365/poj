#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_TIME = 10000;

void init(int a[][100]) {
    int i, j;
    for (i = 0; i < 100; ++i) {
        for (j = 0; j < 100; ++j) {
            if (i == j) {
                a[i][j] = 0;
            } else {
                a[i][j] = MAX_TIME;
            }
        }
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, i, j, k, contact, number, time, a[100][100];

    while (cin >> n && n > 0) {

        init(a);
        for (i = 0; i < n; ++i) {
            cin >> contact;
            for (j = 0; j < contact; ++j) {
                cin >> number >> time;
                a[i][number - 1] = time;
            }
        }

        for (k = 0; k < n; ++k)
            for (i = 0; i < n; ++i)
                for (j = 0; j < n; ++j)
                    if (i != k && j != k && i != j) {
                        a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
                    }

        int people = -1, ans = MAX_TIME;

        for (i = 0; i < n; ++i) {
            int maxTime = 0;
            for (j = 0; j < n; ++j) {
                maxTime = max(maxTime, a[i][j]);
            }

            if (maxTime < ans) {
                ans = maxTime;
                people = i + 1;
            }
        }

        if (people != -1) {
            cout << people << " " << ans << endl;
        } else {
            cout << "disjoint" << endl;
        }
    }
    return 0;
}