#include <iostream>
#include "List.h"

using namespace std;

int main() {
    List<int> arr;
    arr.push_back(3);
    arr.push_back(6);
    arr.push_back(2);
    cout << arr << "\n";
    arr.push_front(5);
    arr.push_front(7);
    cout << arr << "\n";
    Node<int>* f = arr.find(3);
    cout << f->value << "\n";
    arr.insert(10, f);
    cout << arr << "\n";
    arr.pop(f);
    cout << arr << "\n";
    List<int> arr2;
    arr2.push_back(3);
    arr2.push_back(7);
    arr2.push_front(-1);
    arr2.push_front(-6);
    cout << "----";
    cout << arr << "----\n";
    cout << "----";
    cout << arr2 << "----\n";    
    List<int> arr3 = arr + arr2;
    cout << arr3 << "\n";
    arr3.pop_back();
    arr3.pop_front();
    cout << arr3 << "\n";
    arr3.sort();
    cout << arr3;
}