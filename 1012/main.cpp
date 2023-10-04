#include <iostream>
#include <fstream>

using namespace std;

int ans[13] = {0};

void remove(int *a, int key, int n) {
    for (int i = key; i < n; ++i)
        a[key] = a[key + 1];
}

bool process(int n, int m) {

    int last = 0, a[26], total = 2 * n;

    for (int i = 0; i < 26; ++i)a[i] = i;

    while (total > n) {

        last = (last + m) % total;

        if (a[last] < n) {
            return false;
        }
        if (last + 1 == total) {
            last = 0;
        } else {
            remove(a, last, total);
        }
        total--;
    }
    return true;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    cin >> n;
    while (n > 0) {

        if (ans[n - 1]) {
            cout << ans[n - 1] << endl;
        } else {
            int i;
            for (i = 1; i <= 100000000; ++i) {
                if (process(n, i))break;
            }
            ans[n - 1] = i + 1;
            cout << ans[n - 1] << endl;
        }
        cin >> n;
    }

    return 0;
}