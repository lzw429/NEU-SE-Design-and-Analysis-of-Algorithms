//
// Created by 舒意恒 on 19-4-9.
//

#include <bits/stdc++.h>
#include "../lib/util.h"

double maxVal = -1; // 最大价值
vector<int> sol; // 解向量

template<class T>
class Item { // 物品
public:
    T weight; // 物品重量
    T value; // 物品价值
    int id;

    Item() : weight(0), value(0) {}

    Item(T w, T v) : weight(w), value(v) {}

    /**
     * 运算符重载，按照单位价值重量排序
     * @param item 被比较的item
     * @return item a 单位价值是否大于 item b
     */
    bool operator<(const Item &item) {
        double unitValue1 = value / weight;
        double unitValue2 = item.value / item.weight;
        return unitValue1 > unitValue2;
    }
};

/**
 * 上限函数
 * 用于剪枝，判断当前价值加上剩余物品价值是否可能超过当前搜索到的最大价值
 *
 * @tparam T 模板类型
 * @param start 开始判断的物品
 * @param items 物品集合
 * @return 可能获得更大价值 true，无法获得更大价值 false
 */
template<class T>
bool check(int start, const vector<Item<T>> &items, T remain, T curVal) {
    T tmpVal = 0;
    for (int i = start; i < items.size(); i++) {
        Item<T> item = items[i];
        if (item.weight > remain) {
            T upperBound = remain * item.value / item.weight + tmpVal;
            cout << "Position " << start << ", the upper bound " << upperBound << " is smaller than max value "
                 << maxVal << endl;
            return (upperBound > maxVal);
        } else {
            tmpVal += item.value;
            remain -= item.weight;
        }
        if (tmpVal + curVal > maxVal)
            return true;
    }
    return false;
}

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
    cout << "current value: " << val << ", remaining capacity: " << remain << endl;
    if (val > maxVal) {
        maxVal = val;
        sol.assign(state.begin(), state.end()); // 深拷贝
    }
    if (i == n)
        return;
    T newRemain = remain - items[i].weight; // 背包剩余重量
    if (newRemain >= 0) { // 背包仍有剩余空间，可装载该物品
        state.push_back(1);
        dfs(i + 1, newRemain, items, state, n, val + items[i].value);
    }
    if (check(i + 1, items, remain, val)) { // 上限函数满足，不装载该物品
        if (newRemain >= 0)
            state.pop_back();
        state.push_back(0);
        dfs(i + 1, remain, items, state, n, val);
    }
}

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/input3.2.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp3/output3.2.txt");

    int n; // item 数量
    double c; // 背包容量

    // 数据输入
    ifs >> n;
    ifs >> c;

    vector<Item<double>> items(n);
    vector<int> packed(n, 0);

    double t;
    for (int i = 0; i < n; i++) {
        ifs >> t;
        items[i].weight = t;
        items[i].id = i;
    }
    for (int i = 0; i < n; i++) {
        ifs >> t;
        items[i].value = t;
    }

    sort(items.begin(), items.end()); // 按照物品的单位价值重量进行排序，方便进行剪枝
    vector<int> state; // 当前背包状态
    dfs(0, c, items, state, n, 0.0); // 回溯搜索

    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] == 1) {
            packed[items[i].id] = 1;
        }
    }
    for (int i = 0; i < packed.size(); i++) {
        ofs << packed[i] << " ";
    }
    cout << "\nmax value is " << maxVal << "\n";
    closeFileStream(ifs, ofs);
    return 0;
}
