#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const double q = (1 + sqrt(5.0)) / 2.0;

bool isWythoff(int a, int b) {

    int t;
    if (a > b) t = a, a = b, b = t;
    return (int) ((b - a) * q) == a;

}

void testCase(ofstream &cout) {
    bool b[100000] = {false};
    int i = 1;
    int step = 1;
    while (true) {

        // 最小的没用过的数字
        while (b[i]) i++;

        b[i] = true;
//        cout << "i=" << i << ", j=" << step + i << endl;
        if (isWythoff(i, step + i)) {
//            cout << "isWhthoff" << endl;
        } else {
            cout << "test Failed" << endl;
        }
        if (i + step > 100000) {
//            cout << "i=" << i << ", j=" << step + i << endl;
            break;
        }
        b[i + step] = true;
        i++;
        step++;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    testCase(cout);
    int a, b;
    while (cin >> a >> b) {

        if (isWythoff(a, b)) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }

    return 0;
}