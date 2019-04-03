//
// Created by syh on 19-4-3.
//

#include <bits/stdc++.h>

using namespace std;

int coinChange(vector<int> &coins, int amount) {
    int inf = amount + 1;
    vector<int> dp(amount + 1, inf); // dp 大小比硬币数量多1
    // dp[i] 表示凑出i需要的最少硬币数，dp[i] == inf 表示凑不出i
    dp[0] = 0; // 凑出0需要0块硬币
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coins.size(); j++) {
            int val = coins[j];
            if (val <= i) {
                dp[i] = min(dp[i], dp[i - val] + 1);
            }
        }
    }
    return (dp[amount] == inf) ? -1 : dp[amount];
}

int main() {
    ifstream ifs;
    ofstream ofs;
    ifs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/input2.1.txt");
    ofs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/output2.1.txt");

    int n, amount;
    vector<int> coins;
    ifs >> n;
    for (int i = 0; i < n; i++) {
        int t;
        ifs >> t;
        coins.push_back(t);
    }
    ifs >> amount;
    ifs.close();

    ofs << coinChange(coins, amount);
    cout << coinChange(coins, amount);
    ofs.close();
    return 0;
}