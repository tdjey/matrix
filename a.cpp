#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    Matrix<long long> bebra(3, 4), bebra2(3, 3);
    cin >> bebra >> bebra2;
    try {
        pair<string, vector<long double>> solution = bebra.gauss();
        if ( solution.first != "")
            cout << solution.first;
        else {
            for (long double u : solution.second)
                cout << u << " ";
        }
        cout << "\n";
        cout << bebra2.inverse();
    }
    catch (string error) {
        cout << error;
    }
}