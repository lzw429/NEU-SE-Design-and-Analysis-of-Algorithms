//
// Created by syh on 19-4-9.
//

#include <bits/stdc++.h>
#include "../lib/util.h"

using namespace std;

double maxVal = -1;

template<class T>
void
dfs(int start, vector<int> state, vector<vector<int>> &res, const vector<T> &w, T remain1, T remain2, int n, T val) {
    print(state);
    cout << "value: " << val << endl;
    if (start == n) {
        if (val > maxVal) {
            maxVal = val;
            res.push_back(state);
        }
        return;
    }
    for (int i = start; i < n; i++) {
        state.push_back(1);
        if (remain1 - w[i] > 0)
            dfs(start + 1, state, res, w, remain1 - w[i], remain2, n, val + w[i]);
        if (remain2 - w[i] > 0)
            dfs(start + 1, state, res, w, remain1, remain2 - w[i], n, val + w[i]);
        state.pop_back();
        state.push_back(0);
    }
}

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/input3.1.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/output3.1.txt");

    int n;
    double c1, c2;
    vector<double> w;
    ifs >> n >> c1 >> c2;
    for (int i = 0; i < n; i++) {
        double t;
        ifs >> t;
        w.push_back(t);
    }

    vector<int> state;
    vector<vector<int>> res;
    dfs(0, state, res, w, c1, c2, n, 0.0);

    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    ofs << maxVal;
    cout << "max count: " << maxVal;
    closeFileStream(ifs, ofs);
    return 0;
}