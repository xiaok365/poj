#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 101

struct Rectangle {
    double x1, y1, x2, y2;
    int y1_i, y2_i;
};

struct Point {
    double v;
    int index;
    bool top_left;

    Point() {}

    Point(double v, int i, int t) : v(v), index(i), top_left(t) {}

    bool operator<(const Point &other) const {
        return v < other.v;
    }
};

struct SegmentNode {
    int l, r, cnt, extra;
    SegmentNode *lson, *rson;

    SegmentNode() : l(0), r(0), cnt(0), extra(0), lson(NULL), rson(NULL) {}

    SegmentNode(int l, int r) : l(l), r(r), cnt(0), extra(0) {
        lson = rson = NULL;
    }
};

SegmentNode arr[MAX_N * 10];
int node_cnt;

Rectangle a[MAX_N];
Point point_x[MAX_N * 2], point_y[MAX_N * 2];
int n, cnt;
double origin[MAX_N * 2];

SegmentNode *new_node(int l, int r) {
    arr[node_cnt] = SegmentNode(l, r);
    return &arr[node_cnt++];
}

SegmentNode *build_tree(int l, int r) {
    if (l >= r) return NULL;
    if (l + 1 == r) return new_node(l, r);
    SegmentNode *p = new_node(l, r);
    int mid = (l + r) / 2;
    p->lson = build_tree(l, mid);
    p->rson = build_tree(mid, r);
    return p;
}

void push_down(SegmentNode *root) {
    if (root->lson == NULL || root->rson == NULL || root->extra == 0) return;
    root->lson->cnt += root->extra;
    root->lson->extra += root->extra;
    root->rson->cnt += root->extra;
    root->rson->extra += root->extra;
    root->extra = 0;
}

void update(SegmentNode *root, int line_x, int line_y, int data) {
    if (root == NULL || root->r <= line_x || root->l >= line_y) return;
    if (root->l >= line_x && root->r <= line_y) {
        root->cnt += data, root->extra += data;
        return;
    }
    push_down(root);
    update(root->lson, line_x, line_y, data);
    update(root->rson, line_x, line_y, data);
}

double query(SegmentNode *root) {
    if (root == NULL) return 0;
    if (root->cnt > 0) return origin[root->r] - origin[root->l];
    push_down(root);
    return query(root->lson) + query(root->rson);
}

double solve() {
    SegmentNode *root;
    root = build_tree(0, cnt);
    double ans = 0, width, height;
    for (int i = 0; i < 2 * n; ++i) {
        if (i > 0) width = point_x[i].v - point_x[i - 1].v;
        else width = 0;
        height = query(root);
        ans += width * height;
        int l = a[point_x[i].index].y1_i;
        int r = a[point_x[i].index].y2_i;
        if (point_x[i].top_left) {
            update(root, l, r, 1);
        } else {
            update(root, l, r, -1);
        }
    }
    return ans;
}

void init() {
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
        point_x[i] = Point(a[i].x1, i, true);
        point_x[i + n] = Point(a[i].x2, i, false);
        point_y[i] = Point(a[i].y1, i, true);
        point_y[i + n] = Point(a[i].y2, i, false);
    }
    sort(point_x, point_x + 2 * n);
    sort(point_y, point_y + 2 * n);
    // 离散y
    int last, cur;
    cnt = node_cnt = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (i > 0 && point_y[i].v - point_y[i - 1].v < 1e-6) {
            cur = last;
        } else {
            cur = ++cnt;
            origin[cur] = point_y[i].v;
        }
        if (point_y[i].top_left) a[point_y[i].index].y1_i = cur;
        else a[point_y[i].index].y2_i = cur;
        last = cur;
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int cases = 0;
    while (scanf("%d", &n) && n > 0) {
        init();
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++cases, solve());
    }
    return 0;
}
