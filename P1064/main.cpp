#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, k, a[10000], left = 0, right = 0, mid, sum;

    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        double s;
        cin >> s;
        a[i] = int(ceil(s * 100));
        right = max(right, a[i]);
    }

    while (left + 1 < right) {

        mid = (left + right) >> 1;
        sum = 0;
        for (int i = 0; i < n; ++i) sum += a[i] / mid;
        if (sum < k) {
            right = mid;
        } else {
            left = mid;
        }
    }

    sum = 0;
    for (int i = 0; i < n; ++i) sum += a[i] / right;
    if (sum >= k) {
        cout << fixed << setprecision(2) << double(right) / 100 << endl;
    } else {
        cout << fixed << setprecision(2) << double(left) / 100 << endl;
    }
    return 0;
}