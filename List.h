#include "Node.h"
#include <iostream>

using namespace std;

template<typename T>
class List {
    Node<T>* start;
public:
    List() {
        start = nullptr;
    }
    /*~List() {
        Node<T>* cur = start;
        while (cur != nullptr) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        delete cur;
    }*/
    template<typename Type>
    List(const List<Type>& b) {
        start = b.start;
    }
    void push_back(T value) {
        Node<T>* new_elem = new Node<T>(value);
        if (empty())
            start = new_elem;
        else {
            Node<T>* cur = start;
            while (cur->next != nullptr)
                cur = cur->next;
            cur->next = new_elem;
        }
    }
    void push_front(T value) {
        Node<T>* new_elem = new Node<T>(value);
        new_elem->next = start;
        start = new_elem;
    }
    T pop_back() {
        if (empty())
            throw string("pop_back: list is already empty");
        Node<T>* cur = start, * prev = nullptr;
        while (cur->next != nullptr) {
            prev = cur;
            cur = cur->next;
        }
        T ans = cur->value;
        delete cur;
        if (prev)
            prev->next = nullptr;
        else
            start = nullptr;
        return ans;
    }
    T pop_front() {
        if (empty())
            throw string("pop_front: list is already empty");
        T ans = start->value;
        Node<T>* new_start = start->next;
        delete start;
        start = new_start;
        return ans;
    }
    bool empty() {
        return start == nullptr;
    }
    void insert(int value, Node<T>* pointer) {
        Node<T>* cur = start, * prev = nullptr;
        while (cur && cur != pointer) {
            prev = cur;
            cur = cur->next;
        }
        if (cur != pointer)
            throw string("Insert: pointer is invalid");
        Node<T>* new_elem = new Node<T>(value);
        if (prev) {
            new_elem->next = prev->next;
            prev->next = new_elem;
        }
        else {
            new_elem->next = start;
            start = new_elem;
        }
    }
    T pop(Node<T>* pointer) {
        Node<T>* cur = start, * prev = nullptr;
        while (cur && cur != pointer) {
            prev = cur;
            cur = cur->next;
        }
        if (cur != pointer)
            throw string("Pop: pointer is invalid");
        T ans = cur->value;
        if (prev) {
            prev->next = cur->next;
            delete cur;
        }
        else {
            start = cur->next;
            delete cur;
        }
        return ans;
    }
    Node<T>* find(T value) {
        Node<T> * cur = start;
        while (cur && cur->value != value) 
            cur = cur->next;
        return cur;
    }
    T pop(T value) {
        Node<T>* cur = start, * prev = nullptr;
        while (cur && cur->value != start) {
            prev = cur;
            cur = cur->next;
        }
        if (!cur)
            throw string("Pop: element is not presented");
        if (prev) {
            T ans = cur->value;
            prev->next = cur->next;
            delete cur;
            return ans;
        }
        else {
            start = cur->next;
            T ans = cur->value;
            delete cur;
            return ans;
        }
    }

    void clear() {
        Node<T>* cur = start;
        while (cur) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    int size() {
        Node<T>* cur = start;
        int ans = 0;
        while (cur) {
            cur = cur->next;
            ans++;
        }
        return ans;
    }

    void sort() {
        int power = 1, n = size();
        while (power < n) {
            List<T> ans;
            Node<T>* first = start, * second = start;
            for (int j = 0; j < power && second; j++)
                second = second->next;
            int ind_f = 0, ind_s = power;
            while (ind_s != n) {
                int ind2_f = ind_s, ind2_s = min(ind_s + power, n - 1);
                while (ind_f != ind2_f || ind_s != ind2_s) {
                    if (ind_f == ind2_f) {
                        ind_s++;
                        ans.push_back(second->value);
                        second = second->next;
                    }
                    else if (ind_s == ind2_s) {
                        ind_f++;
                        ans.push_back(first->value);
                        first = first->next;
                    }
                    else {
                        if (first->value < second->value) {
                            ans.push_back(first->value);
                            ind_f++;
                            first = first->next;
                        }
                        else {
                            ans.push_back(second->value);
                            ind_s++;
                            second = second->next;
                        }
                    }
                }
                first = second;
                ind_f = ind_s;
                ind_s += power;
                for (int j = 0; j < power && second; j++)
                    second = second->next;
                cout << ans << "\n";
            }
            while (second)
                second = second->next;
            clear();
            start = ans.start;
            power <<= 1;
            
        }
    }

    template<typename Type>
    friend ostream& operator<<(ostream&, const List<Type>&);

    template<typename Type>
    friend List<Type> operator+(const List<Type>&, const List<Type>&);
};

template<typename Type> 
List<Type> operator+(const List<Type>& a, const List<Type>& b) {
    List<Type> ans;
    Node<Type>* cur = a.start;
    while (cur) {
        ans.push_back(cur->value);
        cur = cur->next;
    }
    cur = b.start;
    while (cur) {
        ans.push_back(cur->value);
        cur = cur->next;
    }
    return ans;
}

template<typename Type>
ostream& operator<<(ostream& output, const List<Type>& arr) {
    Node<Type>* cur = arr.start;
    while (cur != nullptr) {
        output << cur->value << " ";
        cur = cur->next;
    }
    return output;
}