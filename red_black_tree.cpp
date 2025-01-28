#include <iostream>
using namespace std;

struct Node {
    int key;
    string color;
    Node* left;
    Node* right;
    Node* p;

    Node(int key)
        : key(key)
        , color("RED")
        , left(nullptr)
        , right(nullptr)
        , p(nullptr)
    {}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void left_rotate(Node* x) {
        Node* y = x->right; // yはxの右の子
        x->right = y->left; // yの左の子をxの右の子にする
        if (y->left != NIL) { // yの左の子がNILでない場合
            y->left->p = x; // yの左の子の親をxにする
        }
        y->p = x->p; // yの親をxの親にする
        if (x->p == NIL) { // xの親がNILの場合
            root = y; // yを根にする
        } else if (x == x->p->left) { // xがxの親の左の子の場合
            x->p->left = y; // xの親の左の子をyにする
        } else { // xがxの親の右の子の場合
            x->p->right = y; // xの親の右の子をyにする
        }
        y->left = x; // yの左の子をxにする
        x->p = y; // xの親をyにする
    }

    void right_rotate(Node* x) {
        Node* y = x->left; // yはxの左の子
        x->left = y->right; // yの右の子をxの左の子にする
        if (y->right != NIL) { // yの右の子がNILでない場合
            y->right->p = x; // yの右の子の親をxにする
        }
        y->p = x->p; // yの親をxの親にする
        if (x->p == NIL) { // xの親がNILの場合
            root = y; // yを根にする
        } else if (x == x->p->right) { // xがxの親の右の子の場合
            x->p->right = y; // xの親の右の子をyにする
        } else { // xがxの親の左の子の場合
            x->p->left = y; // xの親の左の子をyにする
        }
        y->right = x; // yの右の子をxにする
        x->p = y; // xの親をyにする
    }

    void insert_fixup(Node* z) {
        while (z->p->color == "RED") {
            if (z->p == z->p->p->left) {// zの親は左の子？
                Node* y = z->p->p->right; // yはzの叔父である
                if (y->color == "RED") { // zの親も維持も赤？
                    z->p->color = "BLACK"; // ケース1
                    y->color = "BLACK";
                    z->p->p->color = "RED";
                    z = z->p->p;
                } else {
                    if (z == z->p->right) { // ケース2
                        z = z->p;
                        left_rotate(z);
                    }
                    z->p->color = "BLACK"; // ケース3
                    z->p->p->color = "RED";
                    right_rotate(z->p->p);
                }
            } else {
                Node* y = z->p->p->left;
                if (y->color == "RED") {
                    z->p->color = "BLACK";
                    y->color = "BLACK";
                    z->p->p->color = "RED";
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        right_rotate(z);
                    }
                    z->p->color = "BLACK";
                    z->p->p->color = "RED";
                    left_rotate(z->p->p);
                }
            }
        }
        root->color = "BLACK";
    }

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    void insert(int key) {
        Node* z = new Node(key); // 新しいノードを作成
        z->left = z->right = NIL; // 新しいノードの左右の子をNILにする

        Node* x = root; // zと比較中の節点
        Node* y = NIL; // yはzの親になる

        while (x != NIL) { // 番兵に到達するまで繰り返す
            y = x; 
            if (z->key < z->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->p = y; // 場所を見つける、zの親をyにする
        if (y == NIL) {
            root = z; // 木は空であった
        } else if (z->key < y->key) {
            y->left = z; // zをyの左の子にする
        } else {
            y->right = z; // zをyの右の子にする
        }
        z->left = z->right = NIL;
        z->color = "RED";
        insert_fixup(z);
    }

};


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}