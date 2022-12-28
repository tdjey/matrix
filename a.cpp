#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Heap {
    vector<T> arr;
    int n, inf;
public:
    Heap(int n_) {
        n = n_;
        arr.resize(n);
        inf = 1e9;
    }
    Heap() {
        n = 0;
        inf = 1e9;
    }
    bool empty() {
        return n == 0;
    }
    void build() {
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        for (int i = n - 1; i >= 0; i--)
            sift_down(i);
    }
    void sift_down(int x) {
        while (x < n) {
            int index = x;
            if (x * 2 + 2 < n) {
                if (arr[x * 2 + 1] >= arr[x * 2 + 2])
                    index = x * 2 + 1;
                else
                    index = x * 2 + 2;
            }
            else if (x * 2 + 1 < n)
                index = x * 2 + 1;
            if (arr[x] < arr[index]) {
                swap(arr[x], arr[index]);
                x = index;
            }
            else
                break;
        }
    }
    int sift_up(int x) {
        while (x > 0 && arr[x] > arr[(x - 1) / 2]) {
            swap(arr[x], arr[(x - 1) / 2]);
            x = (x - 1) / 2;
        }
        return x;
    }
    void add_elem(int value) {
        arr[n] = value;
        sift_up(n);
        n++;
    }
    void delete_max() {
        if (empty())
            throw string("The heap is already empty");
        n--;
        arr[0] = arr[n];
        sift_down(0);
    }
    T get_max() {
        if (empty())
            throw string("The heap is empty");
        return arr[0];
    }
    int set_elem(int index, int value) {
        arr[index] += value;
        return sift_up(index);
    }
    void print() {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
    }
};

int main() {
    int n;
    cin >> n;
    Heap<int> h(n);
    int cur;
    h.build();
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = h.get_max();
        h.delete_max();
    }
    reverse(arr.begin(), arr.end());
    for (int u : arr)
        cout << u << " ";
}