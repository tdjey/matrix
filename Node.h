template<typename T>
class Node {
public:
    T value;
    Node* next, * prev;
    Node* left, * right;
    int left_sz, right_sz;
    Node(T value) : value(value) {
        next = prev = nullptr;
        left = right = this;
        left_sz = right_sz = 0;
    }
    Node() {
        next = prev = nullptr;
        left = right = this;
        left_sz = right_sz = 0;
        value = -1;
    }
};