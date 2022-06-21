#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    bool a[200];
    while (cin >> n && n != -1) {

        memset(a, false, 200);
        int ans = 0;
        while (n != 0) {
            a[n] = true;
            if (a[n * 2]) {
                ans++;
            }
            if ((n & 1) == 0 && a[n >> 1]) {
                ans++;
            }
            cin >> n;
        }
        cout << ans << endl;

    }
    return 0;
}