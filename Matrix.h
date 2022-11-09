#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
    vector<vector<T>> data;
    int n, m;
public:
    Matrix() {}
    Matrix(vector<vector<T>> _data) : data(_data) {
        n = (int)data.size();
        if (n > 0)
            m = (int)data[0].size();
    }
    Matrix(int n, int m, bool make_identity = false) : n(n), m(m) {
        data.resize(n);
        fill(data.begin(), data.end(), vector<T>(m));
        if (make_identity) {
            for (int i = 0; i < min(n, m); i++)
                    data[i][i] = 1;
        }
    }
    pair<int, int> get_size() const{
        return { n, m };
    }

    Matrix operator+ (Matrix& a) {
        if (a.get_size() != make_pair(n, m))
            throw string("Sizes of matrices are different\n");
        Matrix ans(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.data[i][j] = data[i][j] + a.data[i][j];
        return ans;
    }
    Matrix operator* (T k) {
        Matrix ans(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.data[i][j] = data[i][j] * k;
        return ans;
    }

    Matrix operator*(const Matrix& a) {
        if (n != a.m)
            throw string("Matrices' sizes do not fit\n");
        Matrix ans(n, a.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < a.m; j++)
                for (int k = 0; k < m; k++)
                    ans.data[i][j] += data[i][k] * a.data[k][j];
        return ans;
    }

    Matrix operator%(int mod) {
        if (mod <= 0)
            throw string("Module value must be >= 0");
        Matrix ans(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.data[i][j] = data[i][j] % mod;
        return ans;
    }

    void operator=(const Matrix& a) {
        data = a.data;
        n = a.n;
        m = a.m;
    }

    Matrix transpose() {
        Matrix ans(m, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.data[j][i] = data[i][j];
        return ans;
    }

    Matrix bin_pow(int k, int mod) {
        if (n != m)
            throw string("Matrix is not square\n");
        if (k <= 0)
            throw string("Power is incorrect\n");
        Matrix ans(n, n, true), base = *this;
        while (k) {
            if (k & 1)
                ans = (ans * base) % mod;
            base = (base * base) % mod;
            k >>= 1;
        }
        return ans;
    }
    template<typename Type> friend istream& operator>>(istream& input, Matrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream& output, const Matrix<Type>&);
};

template<typename T>
istream& operator>>(istream& input, Matrix<T>& m) {
    pair<int, int> m_size = m.get_size();
    for (int i = 0; i < m_size.first; i++)
        for (int j = 0; j < m_size.second; j++)
            input >> m.data[i][j];
    return input;
}

template<typename T>
ostream& operator<<(ostream& output, const Matrix<T>& m) {
    pair<int, int> m_size = m.get_size();
    for (int i = 0; i < m_size.first; i++) {
        for (int j = 0; j < m_size.second; j++)
            output << m.data[i][j] << " ";
        output << "\n";
    }
    return output;
}