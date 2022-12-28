#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void quick_sort(vector<int>& arr, int l, int r) {
    if (r - l == 0)
        return;
    if (r - l == 1) {
        if (arr[l] > arr[r])
            swap(arr[l], arr[r]);
        return;
    }
    int l1 = l, r1 = r;
    int pivot = arr[(r + l) / 2];
    while (r >= l) {
        if (arr[l] >= pivot && arr[r] <= pivot) {
            swap(arr[l], arr[r]);
            l++;
            r--;
            continue;
        }
        if (arr[l] <= pivot)
            l++;
        if (arr[r] >= pivot)
            r--;
    }
    quick_sort(arr, l1, r);
    quick_sort(arr, l, r1);
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
    quick_sort(arr, 0, n - 1);
    long double seconds = (clock() - ticks) / (long double)(CLOCKS_PER_SEC);
    cout << seconds;
    ofstream out;
    out.open("check.txt");
    for (int i = 0; i < n; i++)
        out << arr[i] << " ";
}