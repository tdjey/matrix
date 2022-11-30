#include <iostream>
#include "List.h"
#include <string>

using namespace std;

int main() {
    List<int> arr;
    cout << "Hello there, test my new double-linked list:\n";
    cout << "---Options: ---\n 1 - is list empty\n 2 [value] - add element to the beginning\n";
    cout << " 3 [value] - add element to the end\n 4 [value] - add element before the cursor\n";
    cout << " 5 - delete first element\n 6 - delete last element\n";
    cout << " 7 - delete the element the cursor is pointing at\n";
    cout << " 8 - move forward\n 9 - move backward\n 10 - print the list\n 11 - show this again\n 12 - quit :(\n";
    cout << "---Have fun!---\n";
    string cmd;
    while (cmd != "12") {
        cin >> cmd;
        try {
            int int_cmd = stoi(cmd), arg;
            string s_arg;
            if (int_cmd <= 0 || int_cmd > 12)
                throw string("You skipped the options bar, didn't you?");
            switch (int_cmd) {
            case 1:
                cout << (arr.empty() ? "List is empty\n" : "List is not empty\n");
                break;
            case 2:
                cin >> s_arg;
                arg = stoi(s_arg);
                arr.push_front(arg);
                break;
            case 3:
                cin >> s_arg;
                arg = stoi(s_arg);
                arr.push_back(arg);
                break;
            case 4:
                cin >> s_arg;
                arg = stoi(s_arg);
                arr.insert(arg);
                break;
            case 5:
                arr.pop_front();
                break;
            case 6:
                arr.pop_back();
                break;
            case 7:
                arr.pop();
                break;
            case 8:
                arr.go_f();
                break;
            case 9:
                arr.go_b();
                break;
            case 10:
                cout << arr << "\n";
                break;
            case 11:
                cout << "Hello there, test my new double-linked list:\n";
                cout << "---Options: ---\n 1 - is list empty\n 2 [value] - add element to the beginning\n";
                cout << " 3 [value] - add element to the end\n 4 [value] - add element before the cursor\n";
                cout << " 5 - delete first element\n 6 - delete last element\n";
                cout << " 7 - delete the element the cursor is pointing at\n";
                cout << " 8 - move forward\n 9 - move backward\n 10 - print the list\n 11 - show this again\n 12 - quit :(\n";
                cout << "---Have fun!---\n";
                break;
            }
        }
        catch (string e) {
            cout << e << "\n";
        }
        catch (...) {
            cout << "Problems while parsing, please enter correct values :/ !\n";
        }
    }
    cout << "Bye!";
}