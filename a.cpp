#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    Matrix<long long> bebra(2, 2);
    cin >> bebra;
    try {
        cout << bebra.det();
    }
    catch (string error) {
        cout << error;
    }
}