#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    string left;
    string right;
    string balance;
};

bool verify(Node a[], int letter, int balance) {

    char s = char(letter + 65);

    for (int i = 0; i < 3; ++i) {

        long leftP = a[i].left.find(s);
        long rightP = a[i].right.find(s);
        //不包括但不平衡
        if (leftP == -1 && rightP == -1) {
            if (a[i].balance != "even") return false;
            else continue;
        }

        switch (balance) {
            // 轻的
            case 0:
                if (!(leftP >= 0 && a[i].balance == "down"
                      || rightP >= 0 && a[i].balance == "up")) {
                    return false;
                }
                break;
                // 重的
            case 1:
                if (!(leftP >= 0 && a[i].balance == "up"
                      || rightP >= 0 && a[i].balance == "down")) {
                    return false;
                }
                break;
            default:
                break;
        }
    }

    return true;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    Node a[3];

    cin >> n;
    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < 3; ++j) {
            cin >> a[j].left >> a[j].right >> a[j].balance;
        }
        for (int k = 0; k < 24; ++k) {
            if (verify(a, k >> 1, k & 1)) {
                if ((k & 1) == 0) {
                    cout << char((k >> 1) + 65) << " is the counterfeit coin and it is light. " << endl;
                } else {
                    cout << char((k >> 1) + 65) << " is the counterfeit coin and it is heavy. " << endl;
                }
                break;
            }
        }
    }

    return 0;
}