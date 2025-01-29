#include <iostream>
using namespace std;

// B木のノードクラス
class BTreeNode {
    int *keys;  // キーを格納する配列
    int t;      // 最小次数（キーの数の範囲を定義）
    BTreeNode **C; // 子ノードへのポインタ配列
    int n;     // 現在のキーの数
    bool leaf; // 葉ノードの場合true、それ以外はfalse
public:
    BTreeNode(int _t, bool _leaf);   // コンストラクタ

    // このノードを根とする部分木に新しいキーを挿入するユーティリティ関数
    // この関数が呼び出される時点で、ノードは満杯でないことが前提
    void insertNonFull(int k);

    // このノードの子yを分割するユーティリティ関数
    // iは子配列C[]におけるyのインデックス
    // この関数が呼び出される時点で、子yは満杯である必要がある
    void splitChild(int i, BTreeNode *y);

    // このノードを根とする部分木の全ノードを走査する関数
    void traverse();

    // このノードを根とする部分木でキーを検索する関数
    BTreeNode *search(int k);   // kが存在しない場合はNULLを返す

    // 木構造を表示するためのヘルパー関数
    void print_tree_helper(string indent, bool last);

// BTreeクラスからprivateメンバーにアクセスできるようにするためのフレンド宣言
friend class BTree;
};

// B木クラス
class BTree{
    BTreeNode *root; // 根ノードへのポインタ
    int t;  // 最小次数
public:
    // コンストラクタ（空の木として初期化）
    BTree(int _t)
    {  root = NULL;  t = _t; }

    // 木を走査する関数
    void traverse()
    {  if (root != NULL) root->traverse(); }

    // 木でキーを検索する関数
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }

    // B木に新しいキーを挿入するメイン関数
    void insert(int k);

    // 木構造を表示する関数
    void print_tree() {
        if (root == NULL) {
            cout << "木は空です" << endl;
            return;
        }
        root->print_tree_helper("", true);
    }
};

// BTreeNodeクラスのコンストラクタ
BTreeNode::BTreeNode(int t1, bool leaf1) {
    // 与えられた最小次数と葉の属性をコピー
    t = t1;
    leaf = leaf1;

    // 可能な最大キー数と子ポインタのためのメモリを確保
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];

    // キーの数を0で初期化
    n = 0;
}

// このノードを根とする部分木の全ノードを走査する関数
void BTreeNode::traverse() {
    // n個のキーとn+1個の子がある。n個のキーと
    // 最初のn個の子を走査
    int i;
    for (i = 0; i < n; i++) {
        // 葉ノードでない場合、keys[i]を表示する前に
        // 子C[i]を根とする部分木を走査
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // 最後の子を根とする部分木を走査
    if (leaf == false)
        C[i]->traverse();
}

// このノードを根とする部分木でキーkを検索する関数
BTreeNode *BTreeNode::search(int k) {
    // k以上の最初のキーを見つける
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // 見つかったキーがkと等しい場合、このノードを返す
    if (keys[i] == k)
        return this;

    // キーが見つからず、これが葉ノードの場合
    if (leaf == true)
        return NULL;

    // 適切な子に進む
    return C[i]->search(k);
}

// B木に新しいキーを挿入するメイン関数
void BTree::insert(int k)
{
    // 木が空の場合
    if (root == NULL)
    {
        // 根のためのメモリを確保
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // キーを挿入
        root->n = 1;  // 根のキー数を更新
    }
    else // 木が空でない場合
    {
        // 根が満杯なら、木の高さが増加
        if (root->n == 2*t-1)
        {
            // 新しい根のためのメモリを確保
            BTreeNode *s = new BTreeNode(t, false);

            // 古い根を新しい根の子にする
            s->C[0] = root;

            // 古い根を分割し、1つのキーを新しい根に移動
            s->splitChild(0, root);

            // 新しい根は2つの子を持つ。新しいキーが
            // どちらの子に入るか決定
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // 根を変更
            root = s;
        }
        else  // 根が満杯でない場合、根に対してinsertNonFullを呼び出す
            root->insertNonFull(k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k) {
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    } else { // If this node is not leaf
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i+1]->n == 2*t-1) {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// 子ノードを分割するユーティリティ関数
// この関数が呼び出される時点で、yは満杯である必要がある
void BTreeNode::splitChild(int i, BTreeNode *y) {
    // yの(t-1)個のキーを格納する新しいノードを作成
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // yの最後の(t-1)個のキーをzにコピー
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    // yの最後のt個の子をzにコピー
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // yのキー数を減らす
    y->n = t - 1;

    // このノードは新しい子を持つため、
    // 新しい子のための空間を作成
    for (int j = n; j >= i+1; j--) // nはこのノードのキー数
        C[j+1] = C[j];

    // 新しい子をこのノードにリンク
    C[i+1] = z;

    // yのキーの1つがこのノードに移動する
    // 新しいキーの位置を見つけ、より大きいキーを1つ前に移動
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    // yの中間のキーをこのノードにコピー
    keys[i] = y->keys[t-1];

    // このノードのキー数を増やす
    n = n + 1;
}

void BTreeNode::print_tree_helper(string indent, bool last) {
    cout << indent;
    if (last) {
        cout << "└─";
        indent += "  ";
    } else {
        cout << "├─";
        indent += "│ ";
    }

    // このノードのキーを表示
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << keys[i];
        if (i < n - 1) cout << ",";
    }
    cout << "]" << endl;

    // 子ノードを表示
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            if (i == n) {
                C[i]->print_tree_helper(indent, true);
            } else {
                C[i]->print_tree_helper(indent, false);
            }
        }
    }
}

int main() {
    int data[] = {5, 90, 14, 4, 15, 25, 29, 8, 31, 36, 2, 38, 46, 48, 98, 10, 13, 49, 86, 23, 72, 93, 52, 32, 88, 56, 60, 64, 40, 83, 17, 66, 73, 20, 62, 76, 80, 53, 82, 92};

    BTree t(4);
    int n = sizeof(data) / sizeof(data[0]);
    cout << "dataのサイズ: " << n << endl;

    for (int i = 0; i < n; i++) {
        t.insert(data[i]);
    }

    cout << "B木の構造:" << endl;
    t.print_tree();
    cout << "\n通常の走査結果:" << endl;
    t.traverse();
    cout << endl;
    
    return 0;
}