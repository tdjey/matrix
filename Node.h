template<typename T>
class Node {
public:
    T value;
    Node* next, * prev;
    Node(T value) : value(value) {
        next = prev = nullptr;
    }
    Node() {
        next = prev = nullptr;
    }
};