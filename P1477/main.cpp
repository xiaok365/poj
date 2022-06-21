#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, a[50], j = 0;

    while (cin >> n && n > 0) {
        int total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total += a[i];
        }
        total /= n;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] > total) {
                ans += a[i] - total;
            }
        }
        j++;
        cout << "Set #" << j << endl;
        cout << "The minimum number of moves is " << ans << "." << endl << endl;
    }
    return 0;
}