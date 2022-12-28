#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void merge_sort(vector<int>& arr, int l, int r) {
    if (r == l)
        return;
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int f = l, s = mid + 1;
    vector<int> cur;
    while (f <= mid || s <= r) {
        if (f == mid + 1)
            cur.push_back(arr[s++]);
        else if (s == r + 1)
            cur.push_back(arr[f++]);
        else {
            if (arr[f] < arr[s])
                cur.push_back(arr[f++]);
            else
                cur.push_back(arr[s++]);
        }
    }
    for (int i = 0; i < (int)cur.size(); i++)
        arr[l + i] = cur[i];
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
    merge_sort(arr, 0, n - 1);
    long double seconds = (clock() - ticks) / (long double)(CLOCKS_PER_SEC);
    cout << seconds;
    ofstream out;
    out.open("check.txt");
    for (int i = 0; i < n; i++)
        out << arr[i] << " ";
}