#include <iostream>
#include <cmath>


#define MAX_N 201

struct Point {
    int x, y;
};

Point node[MAX_N];

int n;
double dist[MAX_N];
bool visit[MAX_N];

double distance(Point a, Point b) {
    return sqrt(pow((double) a.x - (double) b.x, 2) + pow((double) a.y - (double) b.y, 2));
}

void init() {

    memset(visit, false, sizeof visit);
    visit[0] = true;

    dist[0] = 0;
    for (int i = 1; i < n; ++i) {
        dist[i] = distance(node[i], node[0]);
    }
}

double dijkstra() {

    for (int i = 0; i < n - 1; ++i) {

        double min = 2000;
        int k = -1;

        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                k = j;
                min = dist[j];
            }
        }

        if (k == -1) break;

        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j]) {
                double t = distance(node[k], node[j]);
                if (dist[k] > t) t = dist[k];
                if (t < dist[j]) dist[j] = t;
            }
        }
    }

    return dist[1];
}

int main() {

    freopen("../a.in", "r", stdin);

    int index = 0;
    while (scanf("%d", &n) && n != 0) {

        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &node[i].x, &node[i].y);
        }

        init();

        printf("Scenario #%d\n", ++index);
        printf("Frog Distance = %.3lf\n\n", dijkstra());
    }

    return 0;
}
