#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define COLOR_RED  0x0
#define COLOR_BLACK 0x1

struct RBNode {
    int key, value;
    unsigned char color: 1;
    RBNode *lson, *rson, *parent;

    RBNode(int key, int value) {
        this->key = key;
        this->value = value;
        this->color = COLOR_RED;
        this->lson = NULL;
        this->rson = NULL;
        this->parent = NULL;
    }
};

bool isRed(RBNode *p) {
    if (p && p->color == COLOR_RED) {
        return true;
    }
    return false;
}

bool isBlack(RBNode *p) {
    return !isRed(p);
}

RBNode *parentOf(RBNode *p) {
    return p->parent;
}

RBNode *leftOf(RBNode *p) {
    return p->lson;
}

RBNode *rightOf(RBNode *p) {
    return p->rson;
}

bool isEmpty(RBNode *&root) {
    return !root;
}

RBNode *find(RBNode *&root, int key) {

    RBNode *p = root;

    while (p) {
        if (p->key == key) {
            break;
        }
        if (p->key < key) {
            p = p->rson;
        } else {
            p = p->lson;
        }
    }

    return p;
}

RBNode *findMin(RBNode *p) {

    if (!p) {
        return NULL;
    }
    while (p->lson != NULL) {
        p = p->lson;
    }
    return p;
}

RBNode *findMax(RBNode *p) {

    if (!p) {
        return NULL;
    }
    while (p->rson != NULL) {
        p = p->rson;
    }
    return p;
}

RBNode *leftRotate(RBNode *&root, RBNode *x) {
    RBNode *y = x->rson;

    x->rson = y->lson;
    if (y->lson) {
        y->lson->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        root = y;
    } else if (x == leftOf(parentOf(x))) {
        x->parent->lson = y;
    } else {
        x->parent->rson = y;
    }

    y->lson = x;
    x->parent = y;

    return y;
}

RBNode *rightRotate(RBNode *&root, RBNode *y) {
    RBNode *x = y->lson;

    y->lson = x->rson;
    if (x->rson) {
        x->rson->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) {
        root = x;
    } else if (y == leftOf(parentOf(y))) {
        y->parent->lson = x;
    } else {
        y->parent->rson = x;
    }

    x->rson = y;
    y->parent = x;

    return x;
}

void insertFixup(RBNode *&root, RBNode *p) {
    RBNode *parent, *grand_parent, *uncle;

    while ((parent = parentOf(p)) && parent->color == COLOR_RED) {
        grand_parent = parentOf(parent);
        // 父亲在左
        if (parent == leftOf(grand_parent)) {
            uncle = rightOf(grand_parent);
            // case 1 叔叔为红，向上回溯
            if (isRed(uncle)) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                p = grand_parent;
            } else {
                // case 2 叔叔为黑，且当前为右孩子，转case 3
                if (p == rightOf(parent)) {
                    leftRotate(root, parent);
                    RBNode *temp = parent;
                    parent = p;
                    p = temp;
                }
                // case 3 叔叔为黑，且当前为左孩子
                parent->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                rightRotate(root, grand_parent);
            }
        } else {
            // 父亲在右
            uncle = leftOf(grand_parent);
            // case 1 叔叔为红，向上回溯
            if (isRed(uncle)) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                p = grand_parent;
            } else {
                // case 2 叔叔为黑，且当前为左孩子，转case 3
                if (p == leftOf(parent)) {
                    rightRotate(root, parent);
                    RBNode *temp = parent;
                    parent = p;
                    p = temp;
                }
                // case 3 叔叔为黑，且当前为右孩子
                parent->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                leftRotate(root, grand_parent);
            }
        }
    }
    root->color = COLOR_BLACK;
}

void insert(RBNode *&root, RBNode *p) {
    RBNode *exist = find(root, p->key);
    if (exist) {
        exist->value = p->value;
        return;
    }

    RBNode *tail = root, *last = NULL;

    while (tail) {
        last = tail;
        if (p->key < tail->key) {
            tail = tail->lson;
        } else {
            tail = tail->rson;
        }
    }
    p->parent = last;
    if (last == NULL) {
        root = p;
    } else if (p->key < last->key) {
        last->lson = p;
    } else {
        last->rson = p;
    }
    insertFixup(root, p);
}

void removeFixup(RBNode *&root, RBNode *p) {

    RBNode *brother, *parent;

    while (p != root && isBlack(p)) {

        parent = parentOf(p);

        if (p == leftOf(parent)) {
            brother = parent->rson;
            // 兄弟为红 转为case 2,3,4
            if (isRed(brother)) {
                brother->color = COLOR_BLACK;
                parent->color = COLOR_RED;
                leftRotate(root, parent);
                brother = rightOf(parent);
            }
            // 兄弟为黑
            // 兄弟2孩子都黑 case 2，向上回溯
            if (isBlack(brother->lson) && isBlack(brother->rson)) {
                brother->color = COLOR_RED;
                p = parent;
            } else {
                // case 3 左红右黑，转case 4
                if (isBlack(brother->rson)) {
                    brother->color = COLOR_RED;
                    brother->lson->color = COLOR_BLACK;
                    rightRotate(root, brother);
                    brother = rightOf(parent);
                }
                // case 4 右红
                brother->rson->color = COLOR_BLACK;
                brother->color = parent->color;
                parent->color = COLOR_BLACK;
                leftRotate(root, parent);
                break;
            }
        } else {
            brother = parent->lson;
            // 兄弟为红 转为case 2,3,4
            if (isRed(brother)) {
                brother->color = COLOR_BLACK;
                parent->color = COLOR_RED;
                rightRotate(root, parent);
                brother = leftOf(parent);
            }
            // 兄弟为黑
            // 兄弟2孩子都黑 case 2，向上回溯
            if (isBlack(brother->lson) && isBlack(brother->rson)) {
                brother->color = COLOR_RED;
                p = parent;
            } else {
                // case 3 左黑右红，转case 4
                if (isBlack(brother->lson)) {
                    brother->color = COLOR_RED;
                    brother->rson->color = COLOR_BLACK;
                    leftRotate(root, brother);
                    brother = leftOf(parent);
                }
                // case 4 左红
                brother->lson->color = COLOR_BLACK;
                brother->color = parent->color;
                parent->color = COLOR_BLACK;
                rightRotate(root, parent);
                break;
            }
        }
    }

    p->color = COLOR_BLACK;
}

void transplant(RBNode *&root, RBNode *u, RBNode *v) {
    if (!u->parent) {
        root = v;
    } else if (u == leftOf(parentOf(u))) {
        u->parent->lson = v;
    } else {
        u->parent->rson = v;
    }

    if (v) {
        v->parent = u->parent;
    }
}

void remove(RBNode *&root, int key) {

    if (isEmpty(root)) {
        return;
    }

    RBNode *p = find(root, key);
    if (p == NULL) {
        printf("remove failed, key=%d\n", key);
        return;
    }

    // 有2个孩子
    if (p->lson != NULL && p->rson != NULL) {
        // 用后继结点代替待删除结点
        RBNode *replacement = findMin(p->rson);
        p->value = replacement->value;
        p->key = replacement->key;
        p = replacement;
    }

    RBNode *successor;

    if (p->lson != NULL) {
        successor = p->lson;
    } else {
        successor = p->rson;
    }

    if (successor != NULL) {
        transplant(root, p, successor);
        if (p->color == COLOR_BLACK) {
            removeFixup(root, successor);
        }
    } else {
        if (p->color == COLOR_BLACK) {
            removeFixup(root, p);
        }
        transplant(root, p, NULL);
    }

    delete p;
}

//void printTree(RBNode *root) {
//
//    if (root == NULL) {
//        return;
//    }
//    printf("key=%d, color=%d\n", root->key, root->color);
//    printTree(root->lson);
//    printTree(root->rson);
//}
//
int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(RBNode *root) {

    if (root == NULL) {
        return 0;
    }
    return max(getHeight(root->lson) + 1, getHeight(root->rson) + 1);
}

int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    RBNode *root = NULL;

//    srand(time(0));
//    for (int i = 1000; i > 0; --i) {
//        int s = rand() % 1000;
//        RBNode *node = new RBNode{s, s};
//        printf("insert, %d\n", i);
//        insert(root, node);
//        printf("height=%d\n", getHeight(root));
//    }
//
//    for (int i = 1; i <= 3000; ++i) {
//        printf("remove, %d\n", i);
//        int s = rand() % 1000;
//        remove(root, s);
//        printf("height=%d\n", getHeight(root));
//    }

    int code, k, p;
    RBNode *node;
    scanf("%d", &code);
    while (code) {

        switch (code) {
            case 1:
                scanf("%d%d", &k, &p);
                node = new RBNode(p, k);
                insert(root, node);
                break;
            case 2:
                if (isEmpty(root)) {
                    printf("0\n");
                } else {
                    node = findMax(root);
                    if (node) {
                        printf("%d\n", node->value);
                        remove(root, node->key);
                    }
                }
                break;
            case 3:
                if (isEmpty(root)) {
                    printf("0\n");
                } else {
                    node = findMin(root);
                    if (node) {
                        printf("%d\n", node->value);
                        remove(root, node->key);
                    }
                }
                break;
            default:
                break;
        }
        scanf("%d", &code);
    }

    return 0;
}
