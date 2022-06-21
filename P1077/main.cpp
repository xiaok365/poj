#include <iostream>
#include <fstream>

using namespace std;

// 0-9的阶乘
const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int direction[4][2] = {{0,  1},
                       {0,  -1},
                       {-1, 0},
                       {1,  0}};
char path[4] = {'r', 'l', 'u', 'd'};

struct Node {
    int value;
    int space;
    int parent;
    int direction;
};

int cantor(int a[], int n) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int lessThan = 0;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[i]) lessThan++;
        }
        ans += lessThan * FAC[n - i - 1];
    }
    return ans;
}

void decode(int ans[], int x, int n) {
    bool visit[9] = {false};
    for (int i = 0; i < n; ++i) {
        ans[i] = x / FAC[n - i - 1];
        int j, order = 0;
        for (j = 0; j < n; ++j) {
            if (!visit[j]) {
                if (ans[i] == order) break;
                order++;
            }
        }
        ans[i] = j + 1;
        visit[j] = true;
        x %= FAC[n - i - 1];
    }
}

void swap(int a[], int i, int j) {
    a[i] ^= a[j] ^= a[i] ^= a[j];
}

void print(Node queue[], int tail, ofstream &cout) {

    int ans[362880];
    int total = 0;

    while (queue[tail].parent != -1) {
        ans[total++] = queue[tail].direction;
        tail = queue[tail].parent;
    }

    for (int i = total - 1; i >= 0; --i) {
        cout << path[ans[i]];
    }
    cout << endl;
}

bool checkUnsolvable(const int a[]) {

    int total = 0;
    for (int i = 0; i < 8; ++i) {
        if (a[i] == 9) continue;
        for (int j = i + 1; j < 9; ++j) {
            if (a[j] < a[i]) total++;
        }
    }

    return (total & 1) == 1;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a[9], head = 0, tail = 1;
    bool visit[362880] = {false}, found = false;
    Node start = {};
    Node queue[362880];

    for (int i = 0; i < 9; ++i) {
        char ch;
        cin >> ch;
        if (ch == 'x') {
            a[i] = 9;
            start.space = i;
        } else {
            a[i] = ch - '0';
        }
    }
    if (checkUnsolvable(a)) {
        cout << "unsolvable" << endl;
        return 0;
    }
    start.value = cantor(a, 9);
    start.parent = -1;
    start.direction = -1;
    if (start.value == 0) {
        return 0;
    }
    visit[start.value] = true;
    queue[0] = start;
    while (head < tail && !found) {
        Node current = queue[head++];
        int x, y;
        x = current.space / 3;
        y = current.space % 3;
        for (int i = 0; i < 4; ++i) {
            int xx, yy;
            xx = x + direction[i][0];
            yy = y + direction[i][1];
            if (xx >= 0 && xx < 3 && yy >= 0 && yy < 3) {
                int temp[9];
                decode(temp, current.value, 9);
                swap(temp, current.space, xx * 3 + yy);
                Node next;
                next.parent = head - 1;
                next.space = xx * 3 + yy;
                next.direction = i;
                next.value = cantor(temp, 9);
                if (!visit[next.value]) {
                    visit[next.value] = true;
                    queue[tail++] = next;
                    if (next.value == 0) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    print(queue, tail - 1, cout);

    return 0;
}