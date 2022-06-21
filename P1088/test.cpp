#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

#define R 1000
#define C 1000

class Point {
private:
    int x, y;
public:
    Point() : x(0), y(0) {}

    Point(int s, int t) : x(s), y(t) {}

    Point(const Point &t) {
        x = t.x;
        y = t.y;
    }

    int getX() const;

    int getY() const;
};


class Cstack {
private:
    static const int SIZE = R * C;
    int total;
    Point data[SIZE];
public:
    Point top;

    Cstack() : total(0) {}

    void push(const Point &node);

    Point pop();

    bool isNotEmpty() const;
};

const int dir[4][2] = {{0,  -1},
                       {0,  1},
                       {1,  0},
                       {-1, 0}};

Point father[R][C];
int row, column, map[R][C], f[R][C], answer = 0;
ifstream fin("a.in");
ofstream fout("a.out");

void init() {
    memset(f, -1, sizeof(f));
    fin >> row >> column;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fin >> map[i][j];
        }
    }
}

int main() {
    init();
    Cstack stack;

    double startTime = clock();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {

            if (f[i][j] != -1) {
                continue;
            }

            // 根结点
            father[i][j] = Point(-1, -1);
            stack.push(Point(i, j));

            while (stack.isNotEmpty()) {
                Point start = stack.top;
                // 如果已经计算过，则出栈
                if (f[start.getX()][start.getY()] != -1) {
                    int fx, fy;
                    fx = father[start.getX()][start.getY()].getX();
                    fy = father[start.getX()][start.getY()].getY();
                    if (fx >= 0 && fy >= 0) {
                        f[fx][fy] = max(f[fx][fy], f[start.getX()][start.getY()] + 1);
                    }
                    stack.pop();
                    continue;
                }
                f[start.getX()][start.getY()] = 1;
                for (int k = 0; k < 4; k++) {
                    int x = start.getX() + dir[k][0];
                    int y = start.getY() + dir[k][1];

                    // 相邻点合法
                    if (x >= 0 && x < row && y >= 0 && y < column && map[start.getX()][start.getY()] > map[x][y]) {
                        father[x][y] = Point(start.getX(), start.getY());
                        stack.push(Point(x, y));
                    }
                }
            }
            answer = max(answer, f[i][j]);
        }
    }

    fout << answer << endl;

    double endTime = clock();
    fout << "The run time is: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Cstack::push(const Point &node) {
    data[total] = node;
    top = data[total++];
}

Point Cstack::pop() {
    total--;
    top = data[total - 1];
    return data[total];
}

bool Cstack::isNotEmpty() const {
    return total > 0;
}