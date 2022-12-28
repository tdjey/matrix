#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T value;
    int counter;
    Node<T>* left, * right;
    Node() {
        left = right = nullptr;
        counter = 0;
    }
    Node(T value_) {
        value = value_;
        left = right = nullptr;
        counter = 1;
    }
};

template<typename T>
class BinTree {
    Node<T>* root;
    int h;
public:
    BinTree() {
        root = nullptr;
        h = 0;
    }
    void push(T value) {
        Node<T>* cur = root, * prev = nullptr;
        int cur_h = 0;
        while (cur) {
            if (cur->value == value) {
                cur->counter++;
                return;
            }
            prev = cur;
            if (cur->value < value)
                cur = cur->right;
            else
                cur = cur->left;
            cur_h++;
        }
        cur = new Node<T>(value);
        if (root == nullptr)
            root = cur;
        else {
            if (prev->value < cur->value)
                prev->right = cur;
            else
                prev->left = cur;
        }
        h = max(h, cur_h + 1);
    }
    int get_h() {
        return h;
    }
    Node<T>* get_root() {
        return root;
    }
};

template<typename T>
pair<bool, int> is_balanced(Node<T>* cur) {
    pair<bool, int> ans = { true, 1 };
    int first = 0, second = 0;
    if (cur->left) {
        auto ans1 = is_balanced(cur->left);
        ans.first &= ans1.first;
        first = ans1.second;
    }
    if (cur->right) {
        auto ans1 = is_balanced(cur->right);
        ans.first &= ans1.first;
        second = ans1.second;
    }
    if (abs(first - second) > 1)
        ans.first = false;
    ans.second = max(first, second) + 1;
    return ans;
}

template<typename T>
void print(Node<T>* cur) {
    if (cur->left)
        print(cur->left);
    cout << cur->value << " " << cur->counter << "\n";
    if (cur->right)
        print(cur->right);
}

template<typename T>
void print_leaves(Node<T>* cur) {
    if (cur->left)
        print_leaves(cur->left);
    if (cur->right)
        print_leaves(cur->right);
    if (!(cur->left) && !(cur->right))
        cout << cur->value << "\n";
}

int main() {
    int cur;
    BinTree<int> tree;
    while ((cin >> cur) && cur != 0) 
        tree.push(cur);
    print(tree.get_root());
}