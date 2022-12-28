#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int INSERT_SORT_SIZE;

void quick_sort(vector<int>& arr, int l, int r) {
    if (r - l + 1 == INSERT_SORT_SIZE) {
        for (int i = l; i <= r; i++) 
            for (int j = i; j > l && arr[j] < arr[j - 1]; j--)
                swap(arr[j], arr[j - 1]);
        return;
    }   
    if (r == l)
        return;
    if (r - l == 1) {
        if (arr[l] > arr[r])
            swap(arr[l], arr[r]);
        return;
    }
    int l1 = l, r1 = r;
    int p1 = arr[l], p2 = arr[r], p3 = arr[(r + l) / 2];
    if (p1 > p2)
        swap(p1, p2);
    if (p1 > p3)
        swap(p1, p3);
    if (p2 > p3)
        swap(p2, p3);
    int pivot = p2;
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

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    INSERT_SORT_SIZE = stoi(string(argv[1]));
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