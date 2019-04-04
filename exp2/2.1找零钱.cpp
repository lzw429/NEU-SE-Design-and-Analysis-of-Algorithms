//
// Created by syh on 19-4-3.
//

// 本题类似于 LeetCode 322. Coin Change

#include <bits/stdc++.h>
#include "../lib/util.h"

using namespace std;

/**
 * 求出凑到指定金额的最小硬币数
 *
 * 思路近似于完全背包问题
 *
 * @param coins 硬币种类的集合
 * @param amount 指定凑到的金额
 * @return 不能凑出返回-1，能凑出返回硬币数量
 */
int coinChange(vector<int> &coins, int amount) {
    int inf = amount + 1;
    vector<int> dp(amount + 1, inf); // dp 大小比硬币数量多1
    // dp[i] 表示凑出i需要的最少硬币数，dp[i] == inf 表示凑不出i

    /**
     * 动态规划过程
     */
    dp[0] = 0; // 凑出0需要0块硬币
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coins.size(); j++) {
            int val = coins[j];
            if (val <= i) {
                dp[i] = min(dp[i], dp[i - val] + 1);
            }
        }
    }

    /**
     * 打印 dp 数组
     */
    cout << "DP array: " << endl;
    for (int i = 1; i <= amount; i++)
        cout << dp[i] << endl;
    return (dp[amount] == inf) ? -1 : dp[amount];
}

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/input2.1.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/output2.1.txt");

    int n, amount;
    vector<int> coins;
    ifs >> n;
    if (!n) {
        cout << "[Info] The number of coins is 0" << endl;
    }
    for (int i = 0; i < n; i++) {
        int t;
        ifs >> t;
        coins.push_back(t);
    }
    ifs >> amount;
    if (!amount) {
        cout << "[Info] The target amount is 0" << endl;
    }

    int res = coinChange(coins, amount);
    cout << "The result is: " << res << endl;
    ofs << res;

    closeFileStream(ifs, ofs);
    return 0;
}