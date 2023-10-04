#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    double vs, r, c, w;
    int n;
    cin >> vs >> r >> c >> n;
    while (n--) {
        cin >> w;
        cout << fixed << setprecision(3) << r * c * w * vs * sqrt(1 / (r * r * c * c * w * w + 1)) << endl;
    }
    return 0;
}