//
// Created by syh on 19-4-9.
//

#include <bits/stdc++.h>
#include "../lib/util.h"

int maxVal = -1;
vector<int> sol;


template<class T>
void print(const vector<T> &vec) {
    if (vec.empty())
        cout << "empty";
    else
        for (int i = 0; i < vec.size(); i++)
            cout << vec[i] << " ";
    cout << endl;
}

/**
 * 回溯搜索01背包的最优解
 *
 * @tparam T
 * @param start
 * @param remain
 * @param w
 * @param v
 * @param cur
 * @param n
 */
template<class T>
void dfs(int start, int remain, const vector<T> &w, const vector<T> &v, vector<int> cur, int n, int val) {
    print(cur);
    cout << "value: " << val << endl;
    cout << "n: " << n << endl;
    if (start == n) {
        if (val > maxVal) {
            maxVal = val;
            sol.assign(cur.begin(), cur.end());
        }
        return;
    }
    for (int i = start; i < n; i++) {
        cur.push_back(1);
        int newRemain = remain - w[i];
        if (newRemain >= 0)
            dfs(i + 1, newRemain, w, v, cur, n, val + v[i]);
        cur.pop_back();
        cur.push_back(0);
    }
}


int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/input3.2.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/output3.2.txt");

    int n; // # item
    int c; // package capacity
    vector<double> w; // item weight
    vector<double> v; // item value

    // data input
    ifs >> n;
    ifs >> c;
    double t;
    for (int i = 0; i < n; i++) {
        ifs >> t;
        w.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        ifs >> t;
        v.push_back(t);
    }

    vector<int> cur;
    dfs(0, c, w, v, cur, n, 0);

    for (int i = 0; i < sol.size(); i++) {
        ofs << sol[i] << " ";
    }
    cout << "\nmax value is " << maxVal << "\n";
    closeFileStream(ifs, ofs);
    return 0;
}