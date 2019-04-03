//
// Created by syh on 19-4-3.
//

#include <bits/stdc++.h>

const int inf = 0x3f3f3f3f;
using namespace std;

int main() {
    ifstream ifs;
    ofstream ofs;
    ifs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/input2.2.txt");
    ofs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp2/output2.2.txt");

    // 数据输入
    int n;
    ifs >> n;
    vector<vector<int> > cost(n + 1, vector<int>(n + 1, inf));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int t;
            ifs >> t;
            cost[i][j] = t;
            cost[j][i] = t;
        }
    }
    ifs.close();

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (cost[k][i] != inf && cost[k][j] != inf && cost[i][k] + cost[k][j] < cost[i][j])
                    cost[i][j] = cost[i][k] + cost[k][j];
            }
        }
    }
    ofs << cost[1][n];
    ofs.close();
    return 0;
}