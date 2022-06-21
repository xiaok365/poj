#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const double e = 2.7182818284590452354, pi = 3.141592653589793239;

double stirling(double m) {
    return m * (log10(m / e)) + 0.5 * (log10(2.0 * pi * m));
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, m;
    cin >> n;
    while (n--) {
        cin >> m;
        if (m == 1) {
            cout << 1 << endl;
        } else {
            cout << int(stirling(m) + 1) << endl;
        }
    }
    return 0;
}