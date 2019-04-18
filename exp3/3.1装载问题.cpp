//
// Created by 舒意恒 on 19-4-9.
//

// 该装载问题要求尽可能将第一艘船装满
// 实际上可直接使用01背包求解，每个物品的价值等同于重量

#include <bits/stdc++.h>
#include "../lib/util.h"

double maxVal = -1; // 最大价值
vector<int> sol; // 解向量

template<class T>
class Item { // 物品
public:
    T weight; // 物品重量

    Item() : weight(0) {}

    bool operator<(const Item &item) {
        this->weight > item.weight;
    }
};

/**
 * 回溯搜索01背包的最优解
 *
 * @tparam T 模板类型
 * @param i 搜索开始位置
 * @param remain 背包剩余容量
 * @param items 候选物品
 * @param state 当前背包状态，state[i] = 1表示装入物品 i，state[i] = 0 表示未装入物品 i
 * @param n 物品个数
 */
template<class T>
void dfs(int i, T remain, const vector<Item<T>> &items, vector<int> state, int n, T val) {
    cout << "Position " << i << ", current value: " << val << ", remaining capacity: " << remain << endl;
    if (i == n) {
        if (val > maxVal) {
            maxVal = val;
            sol.assign(state.begin(), state.end()); // 深拷贝
        }
        return;
    }
    T newRemain = remain - items[i].weight; // 背包剩余重量
    if (newRemain >= 0) { // 背包仍有剩余空间，可装载该物品
        state.push_back(1);
        dfs(i + 1, newRemain, items, state, n, val + items[i].weight);
    }
    if (val + remain > maxVal) {
        // 当前装载量加剩余装载量可能超过当前获得的最大载重量
        if(newRemain >= 0)
            state.pop_back();
        state.push_back(0);
        dfs(i + 1, remain, items, state, n, val);
    }
}


int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/input3.1.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/output3.1.txt");

    int n; // item 数量
    double c; // 背包容量

    // 数据输入
    ifs >> n;
    ifs >> c;

    vector<Item<double>> items(n);

    double t;
    for (int i = 0; i < n; i++) {
        ifs >> t;
        items[i].weight = t;
    }

    vector<int> state; // 当前背包状态
    dfs(0, c, items, state, n, 0.0);

    for (int i = 0; i < sol.size(); i++) {
        ofs << sol[i] << " ";
    }
    cout << "\nmax value is " << maxVal << "\n";
    closeFileStream(ifs, ofs);
    return 0;
}
