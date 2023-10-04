#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int j = 1;
    while (a != -1) {

        for (int i = 1; i <= 644; ++i) {
            int n = 33 * i + c;
            if ((n - a) % 23 == 0 && (n - b) % 28 == 0) {
                cout << "Case " << j++ << ": the next triple peak occurs in ";
                int ans = n - d;
                if (ans > 21252) { ans %= 21252; }
                else if (ans < 0) {
                    ans = (ans + 21252) % 21252;
                }
                cout << ans << " days." << endl;
                break;
            }
        }
        cin >> a >> b >> c >> d;
    }

    return 0;
}