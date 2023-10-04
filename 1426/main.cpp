#include <iostream>
#include <fstream>

using namespace std;

const int MAXQ = 200;

unsigned long long queue[MAXQ];
bool visit[200];

unsigned long long bfs(int n) {

    int head = 0, tail = 1;
    queue[0] = 1;
    visit[1] = true;
    while (head != tail && tail + 1 != head) {
        unsigned long long now = queue[head++];
        if (now % n == 0) {
            return now;
        }
        now *= 10;
        if (!visit[now % n]) {
            visit[now % n] = true;
            queue[tail] = now;
            tail = (tail + 1) % MAXQ;
            if (tail + 1 == head) cout << "full" << endl;
        }
        now += 1;
        if (!visit[now % n]) {
            visit[now % n] = true;
            queue[tail] = now;
            tail = (tail + 1) % MAXQ;
            if (tail + 1 == head) cout << "full" << endl;
        }
    }
    return 0;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n;
    while (cin >> n && n > 0) {
        memset(visit, false, 200);
        cout << bfs(n) << endl;
    }

    return 0;
}