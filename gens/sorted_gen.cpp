#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

mt19937 azino(time(0));

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    try {
        if (argc < 3)
            throw string("lack of params");        
        string size_s = string(argv[1]), mod_s = string(argv[2]);
        int ELEM = stoi(size_s), MOD = stoi(mod_s);
        vector<int> arr(ELEM);
        for (int i = 0; i < ELEM; i++)
            arr[i] = azino() % MOD;
        sort(arr.begin(), arr.end());
        freopen("input.txt", "w", stdout);
        cout << ELEM << "\n";
        for (int u : arr)
            cout << u << " ";
    }
    catch (string e) {
        cout << e;
    }
}
