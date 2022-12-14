#include <iostream>
#include <vector>

using namespace std;

void quick_sort(int l, int r, vector<int>& arr) {
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
    quick_sort(l1, r, arr);
    quick_sort(l, r1, arr);
}

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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    merge_sort(arr, 0, n - 1);
    for (int u : arr)
        cout << u << " ";

}