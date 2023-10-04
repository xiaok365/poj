#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int maxOfTwo(int a, int b) {
    return a > b ? a : b;
}

int main() {

    ifstream fin("../a.in");
    ofstream fout("../a.out");

    int i, j, n, maxLength = 0;
    fin >> n;

    vector<int> num(n, 0);
    vector<int> f(n, 0);

    for (i = 0; i < n; i++) {
        fin >> num[i];
    }

    for (i = 0; i < n; i++) {
        f[i] = 1;
        for (j = 0; j < i; j++) {
            if (num[i] > num[j]) {
                f[i] = maxOfTwo(f[i], f[j] + 1);
            };
        }
        maxLength = maxOfTwo(maxLength, f[i]);
    }

    fout << maxLength << endl;
    fin.close();
    fout.close();

    return 0;
}