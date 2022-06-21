#include <iostream>
#include <fstream>

using namespace std;

struct Color {
    int r, g, b;
};

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    Color color[16];
    for (int i = 0; i < 16; ++i) {
        cin >> color[i].r >> color[i].g >> color[i].b;
    }

    int a, b, c;
    while (cin >> a >> b >> c && a >= 0) {

        int maxDis = 3 * 255 * 255 + 1;
        int ans = 0;
        for (int i = 0; i < 16; ++i) {
            int t = (color[i].r - a) * (color[i].r - a) + (color[i].g - b) * (color[i].g - b)
                    + (color[i].b - c) * (color[i].b - c);
            if (t < maxDis) {
                ans = i;
                maxDis = t;
            }
        }

        cout << "(" << a << "," << b << "," << c << ") maps to (";
        cout << color[ans].r << "," << color[ans].g << "," << color[ans].b << ")" << endl;
    }

    return 0;
}