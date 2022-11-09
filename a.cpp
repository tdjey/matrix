#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    int k;
    cin >> k;
    Matrix<long long> bebra(2, 2);
    cin >> bebra;
    try {
        cout << bebra.bin_pow(k, 1e9);
    }
    catch (string error) {
        cout << error;
    }
}