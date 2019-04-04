//
// Created by syh on 19-4-3.
//

#include <bits/stdc++.h>
#include "../lib/util.h"

const double inf = 0x3f3f3f3f;
using namespace std;

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/input2.2.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/output2.2.txt");

    // 数据输入
    int n;
    ifs >> n;
    vector<vector<double> > cost(n + 1, vector<double>(n + 1, inf));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double t;
            ifs >> t;
            cost[i][j] = t;
        }
    }

    /**
     * 动态规划
     * Floyd 算法的实现，有向图，仅能从上游移动到下游
     */
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) { // 只从上游到下游，i不必大于等于k
            for (int j = i + 1; j <= n; j++) { // j大于i即可
                if (cost[i][k] != inf && cost[k][j] != inf && cost[i][k] + cost[k][j] < cost[i][j])
                    cost[i][j] = cost[i][k] + cost[k][j];
            }
        }
    }
    ofs << cost[1][n];

    /**
     * 标准输出各顶点之间的最短路径
     */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (cost[i][j] == inf || i > j)
                cout << "inf\t";
            else cout << cost[i][j] << "\t";
        }
        cout << endl;
    }

    closeFileStream(ifs, ofs);
    return 0;
}