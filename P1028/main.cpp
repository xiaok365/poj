#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void init(string command[]) {
    command[0] = "VISIT";
    command[1] = "FORWARD";
    command[2] = "BACK";
    command[3] = "QUIT";
}

int getCmdNo(string command[], const string &st) {
    for (int i = 0; i < 4; ++i) {
        if (command[i] == st) {
            return i;
        }
    }
    return 4;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string command[4], cmd, web;
    string fStack[100], bStack[100];
    int fSize = 0, bSize = 0;

    init(command);
    web = "http://www.acm.org/";

    while (cin >> cmd && getCmdNo(command, cmd) < 3) {

        switch (getCmdNo(command, cmd)) {
            case 0:
                bStack[bSize++] = web;
                cin >> web;
                cout << web << endl;
                fSize = 0;
                break;
            case 1:
                if (fSize > 0) {
                    bStack[bSize++] = web;
                    web = fStack[--fSize];
                    cout << web << endl;
                } else {
                    cout << "Ignored" << endl;
                }
                break;
            case 2:
                if (bSize > 0) {
                    fStack[fSize++] = web;
                    web = bStack[--bSize];
                    cout << web << endl;
                } else {
                    cout << "Ignored" << endl;
                }
                break;
            default:
                break;
        }
    }

    return 0;
}