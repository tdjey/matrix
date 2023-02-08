//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

#define sz(v) (int)v.size()
typedef pair<int, int> pii;

map<string, int> operations
{ {"*", 2}, {"+", 1}, {"-", 1}, {"/", 2},
  {"sin", 5}, {"sqrt", 5}, {"cos", 5},
  {"abs", 5} };
set<string> need_brackets{ "sqrt", "sin" };

int INF = 1e4;

struct Node {
    string sym = "";
    Node* left = nullptr, * right = nullptr;
    Node() {}
    Node(string val) : sym(val) {}
};

void print_inf(Node* root) {
    if (root->right && !root->left) {
        cout << root->sym;
        if (need_brackets.find(root->sym)
            != need_brackets.end()) {
            cout << "(";
            print_inf(root->right);
            cout << ")";
        }
        else
            print_inf(root->right);
        return;
    }
    if (!root->left && !root->right) {
        cout << root->sym;
        return;
    }

    if ((root->left && root->right))
        cout << "(";
    if (root->left)
        print_inf(root->left);
    cout << " " << root->sym << " ";
    if (root->right)
        print_inf(root->right);
    if ((root->left && root->right))
        cout << ")";
}

void build_seg_tree(vector<pii>& seg_tree, vector<int>& base) {
    int n = sz(base), x = sz(seg_tree) / 2;
    for (int i = 0; i < x; i++)
        seg_tree[x - 1 + i] = { INF, i };
    for (int i = 0; i < n; i++)
        seg_tree[x - 1 + i].first = base[i];
    for (int i = x - 2; i >= 0; i--) {
        int left = seg_tree[i * 2 + 1].first,
            right = seg_tree[i * 2 + 2].first;
        if (left < right)
            seg_tree[i] = seg_tree[i * 2 + 1];
        else
            seg_tree[i] = seg_tree[i * 2 + 2];
    }
}

pii query(vector<pii>& seg_tree, int v, int l, int r, int lq, int rq) {
    if (l >= rq || r <= lq)
        return { INF, INF };
    if (l >= lq && r <= rq)
        return seg_tree[v];
    int mid = (l + r) / 2;
    pii left = query(seg_tree, v * 2 + 1, l, mid, lq, rq),
        right = query(seg_tree, v * 2 + 2, mid, r, lq, rq);
    if (left.first < right.first)
        return left;
    return right;
}

Node* calc_inf(vector<string>& s, vector<pii>& seg_tree, int l, int r) {
    if (r == l)
        return nullptr;
    Node* cur = new Node();
    pii cmin = query(seg_tree, 0, 0, sz(seg_tree) / 2, l, r);
    if (cmin.first == INF) {
        for (int i = l; i < r; i++)
            cur->sym += s[i];
    }
    else {
        cur->sym = s[cmin.second];
        cur->left = calc_inf(s, seg_tree, l, cmin.second);
        cur->right = calc_inf(s, seg_tree, cmin.second + 1, r);
    }
    return cur;
}

bool is_sep(char c) {
    if (c == '(' || c == ')' || c == ' ')
        return true;
    string sc = "";
    sc += c;
    if (operations.find(sc) != operations.end())
        return true;
    return false;
}

Node* build_inf_tree(const string& s) {
    vector<int> order;
    int n = sz(s);
    vector<string> cond{ "" };
    for (int i = 0; i < n; i++) {
        if (is_sep(s[i]) && cond.back() != "")
            cond.push_back("");
        if (s[i] != ' ')
            cond.back() += s[i];
        if (is_sep(s[i]) && cond.back() != "")
            cond.push_back("");
    }
    if (cond.back() == "")
        cond.pop_back();
    n = sz(cond);
    int balance = 0;
    vector<string> new_cond;
    bool prev_oper = true;
    for (int i = 0; i < n; i++) {
        if (cond[i] == "(") {
            balance++;
            continue;
        }
        if (cond[i] == ")") {
            balance--;
            continue;
        }
        new_cond.push_back(cond[i]);
        auto it = operations.find(cond[i]);
        if (it != operations.end()) {
            if (prev_oper)
                order.push_back(it->second + balance * 10 + 2);
            else
                order.push_back(it->second + balance * 10);
            prev_oper = true;
        }
        else {
            order.push_back(INF);
            prev_oper = false;
        }
    }
    int x = 1;
    while (x <= sz(order))
        x <<= 1;
    vector<pii> seg_tree(2 * x);
    build_seg_tree(seg_tree, order);
    Node* root = calc_inf(new_cond, seg_tree, 0, sz(order));
    return root;
}

Node* calc_postfix(vector<string>& arr, int& index) {
    Node* cur = new Node();
    cur->sym = arr[index];
    index--;
    if (operations.find(cur->sym) != operations.end()) {
        cur->right = calc_postfix(arr, index);
        cur->left = calc_postfix(arr, index);
    }
    return cur;
}

Node* build_postfix_tree(const string& s) {
    vector<string> cond(1);
    int n = sz(s);
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ')
            cond.push_back("");
        else
            cond.back() += s[i];
    }
    int last_ind = sz(cond) - 1;
    return calc_postfix(cond, last_ind);
}


Node* calc_prefix(vector<string>& arr, int index) {
    Node* cur = new Node();
    cur->sym = arr[index];
    index--;
    if (operations.find(cur->sym) != operations.end()) {
        cur->left = calc_postfix(arr, index);
        cur->right = calc_postfix(arr, index);
    }
    return cur;
}

void print_postfix(Node* root) {
    if (root->left && root->right) {
        print_postfix(root->left);
        print_postfix(root->right);
        cout << root->sym << " ";
    }
    else if (root->left) {
        print_postfix(root->left);
        cout << root->sym;
    }
    else if (root->right) {
        print_postfix(root->right);
        cout << root->sym << " ";
    }
    else
        cout << root->sym << " ";
}

Node* build_prefix(const string& s) {
    Node* root = new Node();
    vector<string> cond(1);
    int n = sz(s);
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ')
            cond.push_back("");
        else
            cond.back() += s[i];
    }
    return calc_prefix(cond, 0);
}


void print_suffix(Node* root) {
    if (root->left && root->right) {
        cout << root->sym << " ";
        print_suffix(root->left);
        print_suffix(root->right);
    }
    else if (root->left) {
        cout << root->sym;
        print_suffix(root->left);
    }
    else if (root->right) {
        cout << root->sym;
        print_suffix(root->right);
    }
    else
        cout << root->sym << " ";
}

int main() { // infix за nlog
    freopen("input.txt", "r", stdin);
    string s;
    getline(cin, s);
    Node* root = build_inf_tree(s);
    print_postfix(root);
}