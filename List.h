#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
class List {
    Node<T>* start = new Node<T>, * end = new Node<T>, * cursor;
    int window;
public:
    List() {
        start->next = end;
        end->prev = start;
        cursor = start;
        window = 20;
    }
    bool empty() {
        return start->next == end && end->prev == start;
    }

    void recalc(Node<T>* v) {
        if (v->prev->value == v->value) {
            v->left_sz = v->prev->left_sz + 1;
            v->left = v->prev->left;
            v->prev->right_sz = 1;
            v->prev->right = v;
        }
        else {
            v->left_sz = 0;
            v->left = v;
            v->prev->right_sz = 0;
            v->prev->right = v->prev;
        }
        if (v->next->value == v->value) {
            v->right_sz = v->next->right_sz + 1;
            v->right = v->next->right;
            v->next->left_sz = v->right_sz;
            v->next->left = v;
        }
        else {
            v->next->left_sz = 0;
            v->next->left = v->next;
            v->right_sz = 0;
            v->right = v;
        }
        if (v->prev->value == v->value && v->next->value == v->value) {
            v->next->left_sz = v->left_sz + 1;
            v->next->left = v->prev->left;
            v->prev->right_sz = v->right_sz + 1;
            v->prev->right = v->next->right;
        }
    }

    int insert(T value) {
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
        recalc(new_elem);
        if (new_elem->left_sz + new_elem->right_sz + 1 >= 3) {
            if (new_elem->right->next != end) {
                int new_val = new_elem->right->next->value;
                new_elem->left->prev->next = new_elem->right->next->next;
                new_elem->right->next->next->prev = new_elem->left->prev;
                cursor = new_elem->right->next->next;
                return (new_elem->left_sz + 1 + new_elem->right_sz) + 2 * insert(new_val);
            }
            else {
                end->prev = new_elem->left->prev;
                new_elem->left->prev->next = end;
                cursor = new_elem->left->prev;
                return new_elem->left_sz + 1 + new_elem->right_sz;
            }
        }
        return 0;
    }

    void set_window(int value) {
        window = value;
    }

    void go_f() {
        if (cursor != end)
            cursor = cursor->next;
    }

    void go_b() {
        if (cursor != start)
            cursor = cursor->prev;
    }

    void render() {
        Node<T>* cur = start;
        string first_line = "", second_line = "", third_line = "";
        int index;
        if (cur == cursor) {
            index = first_line.size();
            first_line += "      ";
            second_line += "--><--";
            third_line += "      ";
        }
        while (cur->next != end) {
            cur = cur->next;
            if (cur == cursor) {
                index = first_line.size();
                first_line += "   ";
                second_line += "-->";
                third_line += "   ";
            }
            first_line += "/---\\ ";
            second_line += "| ";
            second_line += char((int)cur->value + '0');
            second_line += " | " ;
            third_line += "\\---/ ";
            if (cur == cursor) {
                first_line += "   ";
                second_line += "<--";
                third_line += "   ";
            }
        }
        cur = cur->next;
        if (cur == cursor) {
            index = first_line.size();
            first_line += "      ";
            second_line += "--><--";
            third_line += "      ";
        }
        int min_border = max(index - window - 3, 0);
        first_line = first_line.substr(min_border, 2 * window + 6);
        second_line = second_line.substr(min_border, 2 * window + 6);
        third_line = third_line.substr(min_border, 2 * window + 6);
        cout << first_line << "\n" << second_line << "\n" << third_line << "\n";
    }
};