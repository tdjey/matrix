#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
protected: vector<vector<T>> data;
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

    template<typename Type> void operator=(const Matrix<Type>& a) {
        n = a.n;
        m = a.m;
        data.resize(n);
        fill(data.begin(), data.end(), vector<T>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                data[i][j] = (T)a.data[i][j];
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

    T det() {
        if (n != m)
            throw string("Matrix is not square");
        int ans = 0;
        if (n == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        for (int rest = 0; rest < n; rest++) {
            Matrix additional(n - 1, n - 1);
            for (int i = 1; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (j == rest)
                        continue;
                    additional.data[i - 1][(j > rest ? j - 1 : j)] = data[i][j];
                }
            if (rest & 1)
                ans -= data[0][rest] * additional.det();
            else
                ans += data[0][rest] * additional.det();
        }
        return ans;
    }
    pair<string, vector<long double>> gauss() {
        if (n + 1 != m)
            throw string("matrix size is incorrect");
        Matrix additional(n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                additional.data[i][j] = data[i][j];
        if (additional.det() == 0)
            return { "Degenerate", {} };
        Matrix<long double> ans(n, m);
        ans = *this;
        for (int i = 0; i < n; i++) {
            int not_null = i;
            while (ans.data[not_null][i] == 0)
                not_null++;
            swap(ans.data[i], ans.data[not_null]);
            for (int j = i + 1; j < n; j++) {
                long double coef = ans.data[j][i] / ans.data[i][i];
                if (ans.data[j][i] != 0)
                    for (int k = i; k < m; k++)
                        ans.data[j][k] -= ans.data[i][k] * coef;
            }
        }
        vector<long double> ans_arr(n);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++)
                ans_arr[i] -= ans_arr[j] * ans.data[i][j];
            ans_arr[i] += ans.data[i][n];
            ans_arr[i] /= ans.data[i][i];
        }
        return { "", ans_arr };
    }

    Matrix<long double> inverse() {
        if (n != m)
            throw string("Matrix is not square");
        long double det = this->det();
        if (det == 0)
            throw string("Degenerate");
        Matrix<long double> ans(n, n, true), additional;
        additional = *this;
        for (int i = 0; i < n; i++) {
            int not_null = i;
            while (additional.data[not_null][i] == 0)
                not_null++;
            swap(additional.data[i], additional.data[not_null]);
            swap(ans.data[i], ans.data[not_null]);
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                long double coef = additional.data[j][i] / additional.data[i][i];
                if (additional.data[j][i] != 0)
                    for (int k = 0; k < m; k++) {
                        additional.data[j][k] -= additional.data[i][k] * coef;
                        ans.data[j][k] -= ans.data[i][k] * coef;
                    }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                ans.data[i][j] /= additional.data[i][i];
        }
        return ans;
    }

    template<typename Type> friend istream& operator>>(istream& input, Matrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream& output, const Matrix<Type>&);
    friend class Matrix;
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