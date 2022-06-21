#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string st;
    char ch;

    while (cin >> st && st != "ENDOFINPUT") {
        cin >> noskipws >> ch;
        while (cin >> ch && ch != '\n') {
            if (ch >= 'F' && ch <= 'Z') {
                cout << char(ch - 5);
            } else if (ch >= 'A' && ch < 'F') {
                cout << char(ch + 21);
            } else {
                cout << ch;
            }
        }
        cin >> skipws >> st;
        cout << endl;
    }

    return 0;
}