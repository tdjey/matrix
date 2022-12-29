#include <iostream>
#include "List.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;

mt19937 rnd(time(0));

int main() {
    List<int> arr;
    cout << "Hello there, test my new game 'balls':\n";
    cout << "Rules are easy: on each step you are given a ball colored ";
    cout << "in a number from 1 to 9. Make less then 3 steps then insert your ball.";
    cout << " Rows of 3 and more balls are destroyed and you will get some points.";
    cout << " The more complicated your chain is, the more points you'll get (for example: ";
    cout << "destroying balls in a few steps like 2 1 1 1 2 2 -> 2 2 2 -> --- ";
    cout << "costs a lot. Each step will be multiplied by 2).\n";
    cout << "1 - move cursor one ball left\n2 - move cursor one ball right\n";
    cout << "3 - insert ball before the cursor\n4 - end the game\n";
    cout << "---Have fun!---\n";
    string cmd;
    int n = 10;
    int score = 0, steps = 3, next_color = rnd() % 9 + 1;
    arr.go_f();
    for (int i = 0; i < n; i++)
        arr.insert(rnd() % 9 + 1);
    while (score != 0) {
        arr.insert(rnd() % 9 + 1);
        score--;
    }
    for (int i = 0; i < n + 1; i++)
        arr.go_b();
    arr.render();
    cout << "---Your next ball is:---\n";
    cout << "/---\\\n";
    cout << "| " << next_color << " |\n";
    cout << "\\---/\n";
    while (true) {
        cin >> cmd;
        try {
            int int_cmd = stoi(cmd), arg;
            string s_arg;
            if (int_cmd <= 0 || int_cmd > 12)
                throw string("You skipped the options bar, didn't you?");
            switch (int_cmd) {
            case 1:
                if (steps == 0)
                    throw string("You don't have any moves left\n");
                arr.go_b();
                steps--;
                break;
            case 2:
                if (steps == 0)
                    throw string("You don't have any moves left\n");
                arr.go_f();
                steps--;
                break;
            case 3:
                score += arr.insert(next_color);
                next_color = rnd() % 9 + 1;
                steps = 3;
                cout << "---Your next ball is:---\n";
                cout << "/---\\\n";
                cout << "| " << next_color << " |\n";
                cout << "\\---/\n";
                break;
            case 4:
                cout << "Total score: " << score << ". You are amazing\n";
                return 0;
                break;
            }
            arr.render();
            cout << "Current score: " << score << ", Steps left: " << steps << "\n";
        }
        catch (string e) {
            cout << e << "\n";
        }
        catch (...) {
            cout << "Problems while parsing, please enter correct values :/ !\n";
        }
    }
}