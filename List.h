#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
class List {
    Node<T>* start = new Node<T>, * end = new Node<T>, * cursor;
public:
    List() {
        start->next = end;
        end->prev = start;
        cursor = start;
    }
    bool empty() {
        return start->next == end && end->prev == start;
    }
    void push_back(T value) {
        Node<T>* new_elem = new Node<T>(value);
        if (empty()) {
            start->next = new_elem;
            end->prev = new_elem;
            new_elem->next = end;
            new_elem->prev = start;
        }
        else {
            Node<T>* prev_elem = end->prev;
            prev_elem->next = new_elem;
            end->prev = new_elem;
            new_elem->next = end;
            new_elem->prev = prev_elem;
        }
    }
    void push_front(T value) {
        Node<T>* new_elem = new Node<T>(value);
        if (empty()) {
            start->next = new_elem;
            end->prev = new_elem;
            new_elem->next = end;
            new_elem->prev = start;
        }
        else {
            Node<T>* next_elem = start->next;
            next_elem->prev = new_elem;
            start->next = new_elem;
            new_elem->prev = start;
            new_elem->next = next_elem;
        }
    }
    T pop_back() {
        if (empty())
            throw string("pop_back: list is already empty");
        Node<T>* deleted = end->prev;
        deleted->prev->next = end;
        end->prev = deleted->prev;
        T ans = deleted->value;
        if (deleted == cursor)
            cursor = end;
        delete deleted;
        if (empty())
            cursor = start;
        return ans;
    }
    T pop_front() {
        if (empty())
            throw string("pop_front: list is already empty");
        Node<T>* deleted = start->next;
        start->next = deleted->next;
        deleted->next->prev = start;
        T ans = deleted->value;
        if (deleted == cursor)
            cursor = start;
        delete deleted;
        if (empty())
            cursor = start;
        return ans;
    }
    void insert(T value) {
        Node<T>* new_elem = new Node<T>(value);
        if (cursor == start) {
            new_elem->next = start->next;
            new_elem->prev = start;
            start->next = new_elem;
            cursor = new_elem;
        }
        else {
            new_elem->next = cursor;
            new_elem->prev = cursor->prev;
            cursor->prev->next = new_elem;
            cursor->prev = new_elem;
        }
    }
    T pop() {
        if (empty())
            throw string("Can't erase: list is already empty");
        if (cursor == start || cursor == end)
            throw string("Can't erase: cursor is pointing to the non-existing element");
        if (cursor->prev)
            cursor->prev->next = cursor->next;
        if (cursor->next)
            cursor->next->prev = cursor->prev;
        T ans = cursor->value;
        Node<T>* next_elem = cursor->next;
        delete cursor;
        cursor = next_elem;
        return ans;
    }

    void go_f() {
        if (cursor != end)
            cursor = cursor->next;
    }

    void go_b() {
        if (cursor != start)
            cursor = cursor->prev;
    }

    template<typename Type>
    friend ostream& operator<<(ostream&, const List<Type>&);
};

template<typename Type>
ostream& operator<<(ostream& output, const List<Type>& arr) {
    Node<Type>* cur = arr.start->next;
    if (arr.cursor == arr.start)
        output << "--><-- ";
    while (cur != arr.end) {
        if (cur == arr.cursor) 
            output << "--> " << cur->value << " <-- ";
        else
            output << cur->value << " ";
        cur = cur->next;
    }
    if (cur == arr.cursor) 
        output << "--><--";
    return output;
}