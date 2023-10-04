#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    long t, n, five[12];
    long s = 1;

    for (long i = 0; i < 12; ++i) {
        s *= 5;
        five[i] = s;
    }

    cin >> t;
    for (long i = 0; i < t; ++i) {
        cin >> n;
        long ans = 0;
        for (int j = 0; j < 12; ++j) {
            if (five[j] > n) break;
            ans += n / five[j];
        }
        cout << ans << endl;
    }
    return 0;
}