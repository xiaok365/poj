#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    double x, y, pi = 3.14159265;

    cin >> n;

    for (int i = 0; i < n; ++i) {

        cin >> x >> y;

        double year = pi * (x * x + y * y) / 100;

        cout << "Property " << i + 1 << ": This property will begin eroding in year " << ceil(year)
             << "." << endl;
    }

    cout << "END OF OUTPUT." << endl;

    return 0;
}