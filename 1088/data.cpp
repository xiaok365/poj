#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

ofstream fout("a.in");
#define ROW 5
#define COLUMN 5

void data1() {

    fout << ROW << " " << COLUMN << endl;

    srand((int) time(0));  // 产生随机种子  把0换成NULL也行
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            fout << rand() << " ";
        }
        fout << endl;
    }
}

void data2() {
    int left = 0, right = COLUMN - 1, top = 0, bottom = ROW - 1;

    int f[ROW][COLUMN],i = 0, j = 0, num = 1;;
    fout << ROW << " " << COLUMN << endl;
    while (i >= top && i <= bottom && j >= left && j <= right) {

        // left->right
        while (j <= right) {
            f[i][j++] = num++;
        }
        j--;
        top++;
        i++;

        // top->bottom
        while (i <= bottom) {
            f[i++][j] = num++;
        }
        i--;
        right--;
        j--;

        // right->left
        while (j >= left) {
            f[i][j--] = num++;
        }
        j++;
        bottom--;
        i--;

        // bottom->top
        while (i >= top) {
            f[i--][j] = num++;
        }
        i++;
        left++;
        j++;
    }

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            fout << f[i][j] << " ";
        }
        fout << endl;
    }
}

int main() {

    data2();
    return 0;
}

