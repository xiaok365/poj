#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 10001;

int calc(int x) {
    int t = x;
    while (t > 0) {
        x += t % 10;
        t /= 10;
    }
    return x;
}

int main() {

    ofstream cout("../a.out");

    bool a[MAXN] = {false};

    for (int i = 1; i < MAXN; ++i) {
        int j = calc(i);
        if (j <= MAXN) a[j] = true;
    }

    for (int i = 1; i <= MAXN; ++i)
        if (!a[i]) cout << i << endl;

    return 0;
}