#include <iostream>
#include "List.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;

mt19937 rnd(time(0));

int main() {
    List<int> arr;
    cout << "Hello there, test my brand new one-linked-list:\n";
    cout << "1 - is list empty\n2 x - insert element to the start\n";
    cout << "3 x - insert element to the end\n4 - delete first element\n";
    cout << "5 - delete last element\n6 x - delete first element with value equal to x\n";
    cout << "7 x - is there an element with value x\n8 - end\n";
    cout << "---Have fun!---\n";
    string cmd;
    while (true) {
        cin >> cmd;
        try {
            int int_cmd = stoi(cmd), arg;
            string s_arg;
            Node<int>* it;
            if (int_cmd <= 0 || int_cmd > 12)
                throw string("You skipped the options bar, didn't you?");
            switch (int_cmd) {
            case 1:
                if (arr.empty())
                    cout << "Yes\n";
                else
                    cout << "No\n";
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
                arr.pop_front();
                break;
            case 5:
                arr.pop_back();
                break;
            case 6:
                cin >> s_arg;
                arg = stoi(s_arg);
                 it = arr.find(arg);
                if (it)
                    arr.pop(it);
                else 
                    throw string("No element with given value was found");
                break;
            case 7:
                cin >> s_arg;
                arg = stoi(s_arg);
                if (arr.find(arg))
                    cout << "Yes\n";
                else
                    cout << "No\n";
                break;
            case 8:
                cout << "Bye\n";
                return 0;                
            }
            cout << arr << "\n";
        }
        catch (string e) {
            cout << e << "\n";
        }
        catch (...) {
            cout << "Problems while parsing, please enter correct values :/ !\n";
        }
    }
}