#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    double card;

    cin >> card;
    while (card > 0.00) {

        double sum = 0;
        int i;
        for (i = 0; i < 300; ++i) {
            sum += 1 / ((double) i + 2);
            if (sum > card) break;
        }

        cout << i + 1 << " card(s)" << endl;

        cin >> card;
    }

    return 0;
}