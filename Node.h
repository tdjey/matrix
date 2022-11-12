template<typename T>
class Node {
public:
    T value;
    Node* next;
    Node(T value) : value(value) {
        next = nullptr;
    }
};