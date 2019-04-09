//
// Created by syh on 19-4-9.
//

#include <bits/stdc++.h>
#include "../lib/util.h"

double maxVal = -1; // 最大价值
vector<int> sol; // 解向量


/**
 * 回溯搜索01背包的最优解
 *
 * @tparam T 模板类型
 * @param start 搜索开始位置
 * @param remain 背包剩余容量
 * @param w 物品重量
 * @param v 物品价值
 * @param state 当前背包状态，state[i] = 1表示装入物品 i，state[i] = 0 表示未装入物品 i
 * @param n 物品个数
 */
template<class T>
void dfs(int start, T remain, const vector<T> &w, const vector<T> &v, vector<int> state, int n, T val) {
    print(state);
    cout << "value: " << val << endl;
    cout << "n: " << n << endl;
    if (start == n) {
        if (val > maxVal) {
            maxVal = val;
            sol.assign(state.begin(), state.end());
        }
        return;
    }
    for (int i = start; i < n; i++) {
        state.push_back(1);
        T newRemain = remain - w[i];
        if (newRemain >= 0)
            dfs(i + 1, newRemain, w, v, state, n, val + v[i]);
        state.pop_back();
        state.push_back(0);
    }
}


int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/input3.2.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/output3.2.txt");

    int n; // # item
    double c; // package capacity
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

    vector<int> state; // 当前背包状态
    dfs(0, c, w, v, state, n, 0.0);

    for (int i = 0; i < sol.size(); i++) {
        ofs << sol[i] << " ";
    }
    cout << "\nmax value is " << maxVal << "\n";
    closeFileStream(ifs, ofs);
    return 0;
}
