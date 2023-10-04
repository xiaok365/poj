#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");
    
    int n, m;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m;
        int j;
        for (j = 1; j * j <= m; ++j);
        cout << j - 1 << endl;
    }
    return 0;
}