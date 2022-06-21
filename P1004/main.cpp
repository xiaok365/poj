#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    double sum = 0, s;

    for (int i = 0; i < 12; ++i) {
        cin >> s;
        sum += s;
    }

    cout << "$" << sum / 12 << endl;

    cin.close();
    cout.close();
    return 0;
}