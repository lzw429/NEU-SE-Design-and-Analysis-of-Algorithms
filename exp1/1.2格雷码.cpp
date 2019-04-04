//
// Created by syh on 19-4-3.
//

// 生成指定位数的格雷码

#include <bits/stdc++.h>
#include "../lib/util.h"

#define MAX_NUM 1025  // 格雷码数量
#define MAX_BIT 11   // 格雷码的二进制位数

using namespace std;

/**
 * 生成指定位数的格雷码
 *
 * 把原问题分解为两个子问题，分别对两个子问题的每个数组后一位加0和1。
 * 以 mid 为中心，在第 b 位，前 n/2 行填 reverse，后 n/2 行填 1 - reverse
 *
 * @param grayCode 格雷码
 * @param mid 中间位下标
 * @param n 涉及的格雷码的个数
 * @param b 当前位数，初始为1，随递归增加
 * @param reverse 为0则下一位为01，为1则下一位为10
 */
void getGrayCode(vector<vector<int>> &grayCode, int mid, int n, int b, int reverse) {
    if (n == 1)
        return;
    cout << "mid: " << mid << ", nLine: " << n << ", bit: " << b << ", reverse: " << reverse << endl;

    // 第 b 位，包括 mid 的前 n/2 行，填 reverse
    for (int i = mid - n / 2 + 1; i <= mid; i++) {
        grayCode[i][b] = reverse;
        cout << "[" << i << "][" << b << "] ";
    }
    cout << "= " << reverse << endl;

    // 第 b 位，不包含 mid 的后 n/2 行，填 1 - reverse
    for (int j = mid + 1; j < mid + n / 2 + 1; j++) {
        grayCode[j][b] = 1 - reverse;
        cout << "[" << j << "][" << b << "] ";
    }
    cout << "= " << 1 - reverse << endl;

    // 填写下一位
    getGrayCode(grayCode, mid - n / 4, n / 2, b + 1, 0);
    getGrayCode(grayCode, mid + n / 4, n / 2, b + 1, 1);
}

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/input1.2.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/output1.2.txt");

    vector<vector<int>> grayCode(MAX_NUM, vector<int>(MAX_BIT));
    int nBit, nLine;
    ifs >> nBit;
    cout << "nBit: " << nBit << endl;

    nLine = pow(2, nBit); // 格雷码的数量
    getGrayCode(grayCode, nLine / 2, nLine, 1, 0); // 生成格雷码

    // 输出数据
    for (int i = 1; i <= nLine; i++) {
        for (int j = 1; j <= nBit; j++) {
            cout << grayCode[i][j];
            ofs << grayCode[i][j];
        }
        cout << "\n";
        ofs << "\n";
    }

    closeFileStream(ifs, ofs);
    return 0;
}

