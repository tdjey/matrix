#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>

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
    void build(vector<int>& inp) {
        for (int i = 0; i < n; i++)
            arr[i] = inp[i];
        for (int i = n - 1; i >= 0; i--)
            sift_down(i);
    }
    void sift_down(int x) {
        while (x < n) {
            int index = x;
            if (x * 2 + 2 < n) {
                if (arr[x * 2 + 1] < arr[x * 2 + 2])
                    index = x * 2 + 1;
                else
                    index = x * 2 + 2;
            }
            else if (x * 2 + 1 < n)
                index = x * 2 + 1;
            if (arr[x] > arr[index]) {
                swap(arr[x], arr[index]);
                x = index;
            }
            else
                break;
        }
    }
    int sift_up(int x) {
        while (x > 0 && arr[x] < arr[(x - 1) / 2]) {
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    long double ticks = clock();
    Heap<int> h(n);
    h.build(arr);
    for (int i = 0; i < n; i++) {
        arr[i] = h.get_max();
        h.delete_max();
    }
    long double seconds = (clock() - ticks) / (long double)(CLOCKS_PER_SEC);
    cout << seconds;
    ofstream out;
    out.open("check.txt");
    for (int i = 0; i < n; i++)
        out << arr[i] << " ";
}