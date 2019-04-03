//
// Created by syh on 19-4-3.
//


#include <bits/stdc++.h>

#define SIZE_OF_NUM 1025  //格雷码总数
#define SIZE_OF_BIT 11   //格雷码的二进制位数

using namespace std;

void get_Gray_code(int a[SIZE_OF_NUM][SIZE_OF_BIT], int mid, int n, int b, int reverse_or_not);

int main() {
    ifstream ifs;
    ifs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/input1.2.txt");
    ofstream ofs;
    ofs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/output1.2.txt");

    int GrayCode[SIZE_OF_NUM][SIZE_OF_BIT];
    int bit, n;
    printf("input bit: ");
    ifs >> bit;
    cout << bit << endl;
    ifs.close();

    n = pow(2, bit);
    get_Gray_code(GrayCode, n / 2, n, 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= bit; j++) {
            cout << GrayCode[i][j];
        }
        cout << "\n";
    }
    ofs.close();
    return 0;
}

void get_Gray_code(int a[SIZE_OF_NUM][SIZE_OF_BIT], int mid, int n, int b, int reverse_or_not)
//SIZE_OF_NUM格雷码个数    SIZE_OF_BIT 格雷码位数
//mid 中间点序号          n 本次操作格雷码个数   b格雷码位数   reverse_or_not 为0则下一位为01  ，为1则下一位为10
{
    if (n == 1)
        return;
    else {
        for (int i = mid - n / 2 + 1; i <= mid; i++) {
            a[i][b] = reverse_or_not;
        }
        for (int j = mid + 1; j < mid + n / 2 + 1; j++) {
            a[j][b] = 1 - reverse_or_not;
        }
//        if(n>=1)
        {
            get_Gray_code(a, mid - n / 4, n / 2, b + 1, 0);
            get_Gray_code(a, mid + n / 4, n / 2, b + 1, 1);
        }
    }
}