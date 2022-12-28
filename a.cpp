#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int TESTS = 3, ELEM = 1e7, SMALL = 1000, MED = 1e5, LARGE = 1e9;
int SIZE[3] = {1000, 10000, (int)1e7};

bool check() {
    ifstream input;
    input.open("compiled/check.txt");
    int prev_, cur;
    input >> prev_;
    for (int i = 1; i < ELEM; i++) {
        input >> cur;
        if (cur < prev_)
            return false;
    }
    return true;
}

void print(string msg, int tabs = 0) {
    ofstream out;
    out.open("compiled/stats.txt", ios_base::app);
    for (int i = 0; i < tabs * 4; i++)
        out << " ";
    out << msg;
    out.close();
}

void run_cmd(string cmd, string path = "") {
    string test = "cd " + path + " && " + cmd;
    if (path != "")
        system(("cd " + path + " && " + cmd).c_str());
    else
        system(cmd.c_str());
}

void test(string prog, vector<string>& gens) {
    print(prog + "\n");
    for (string gen : gens) {
        print(gen + ":\n");
        string cmd;
        for (int k = 0; k < 2; k++) {
            print("array size: " + to_string(SIZE[k]) + "\n", 1);
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    ELEM = SMALL;
                    print("small elements: (" + to_string(ELEM) + ") ", 2);
                }
                else if (j == 1) {
                    print("med elements: (" + to_string(ELEM) + ") ", 2);
                    ELEM = MED;
                }
                for (int i = 0; i < TESTS; i++) {
                    cmd = gen + ".exe " + to_string(SIZE[k]) + " " + to_string(ELEM);
                    run_cmd(cmd, "compiled");
                    cmd = "<nul set /p  =|" + prog + ".exe >> stats.txt";
                    run_cmd(cmd, "compiled");
                    if (!check())
                        print("!!list is not sorted!!");
                    print(" ");
                }
                print("\n");
            }
        }
        
    }
}

int main() {
    vector<string> programs, gens;
    ifstream input;
    input.open("square_programs.txt");
    string cur;
    while (input >> cur) 
        if (cur != "") 
            programs.push_back(cur);
    input.close();
    input.open("gens.txt");
    while (input >> cur)
        if (cur != "")
            gens.push_back(cur);
    input.close();
    for (int i = 0; i < (int)programs.size(); i++) 
        test(programs[i], gens);
}