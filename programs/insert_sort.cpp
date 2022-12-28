#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void insert_sort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = 0; i < n; i++) 
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            swap(arr[j], arr[j - 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    long double ticks = clock();
    insert_sort(arr);
    long double seconds = (clock() - ticks) / (long double)(CLOCKS_PER_SEC);
    cout << seconds;
    ofstream out;
    out.open("check.txt");
    for (int i = 0; i < n; i++)
        out << arr[i] << " ";
}