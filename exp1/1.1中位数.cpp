//
// Created by syh on 19-4-3.
//

// 本题类似于 LeetCode 4. Median of Two Sorted Arrays
// 两数组长度相等，题目更简单
#include <bits/stdc++.h>
#include "../lib/util.h"

using namespace std;

/**
 * 查找两个排序数组中的中位数
 *
 * O(n)解法，合并数组并获取中位数
 * @param nums1 已排序数组1
 * @param nums2 已排序数组2
 * @return 两数组的中位数
 */
double findMedianSortedArrays1(vector<double> &nums1, vector<double> &nums2) {
    int m = nums1.size();
    int n = nums2.size();

    int i = 0, j = 0, size = 0;
    vector<double> nums(m + n, 0);

    while (size < nums.size()) {
        if (i < m && j < n)
            nums[size++] = (nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
        else if (i < m)
            nums[size++] = nums1[i++];
        else
            nums[size++] = nums2[j++];
    }
    return nums[size / 2 - 1];
}

/**
 * 查找两个排序数组中的中位数
 *
 * 比较两个序列的中位数大小，如果两个数相等，则该数为整个2n个数据的中位数，
 * 否则通过比较，分别减少两个序列的查找范围，确定查找的起止位置，继续查找。
 *
 * O(log_{n})解法，合并数组并获取中位数
 * @param nums1 已排序数组1
 * @param nums2 已排序数组2
 * @return 两数组的中位数
 */
double findMedianSortedArrays2(vector<double> &nums1, vector<double> &nums2) {
    if (nums1.empty() && nums2.empty()) return -1;
    int n1 = nums1.size(), n2 = nums2.size();
    if (n2 < n1) return findMedianSortedArrays2(nums2, nums1);
    // 以下步骤的前提是 nums1 长度大于等于 nums2 长度

    int left = 0, right = n1; // 第一个数组的开始和结束下标 [left, right)
    int half = (n1 + n2 + 1) >> 1; // 两个数组合并后的中间位置

    while (left <= right) {
        int m1 = left + ((right - left) >> 1);
        int m2 = half - m1;

        if (m1 < n1 && nums1[m1] < nums2[m2 - 1]) {
            // 向右搜索
            left = m1 + 1;
        } else if (0 < m1 && nums2[m2] < nums1[m1 - 1]) {
            // 向左搜索
            right = m1;
        } else { // m1 >= n1 or m1 <= 0 or nums1[m1] >= nums2[m2 - 1] or nums2[m2] >= nums1[m1 - 1]
            // 找到结果
            double maxleft = m1 == 0 ? nums2[m2 - 1] :
                             m2 == 0 ? nums1[m1 - 1] : max(nums1[m1 - 1], nums2[m2 - 1]);

            return maxleft;
            /*
            // 根据奇偶计算中位数
            if ((n1 + n2) & 1)
                return maxleft;

            int minright = m1 == n1 ? nums2[m2] :
                           m2 == n2 ? nums1[m1] : min(nums1[m1], nums2[m2]);
            return (maxleft + minright) / 2.0;
             */
        }
    }
    return -1;
}

int main() {
    ifstream ifs = openIfs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/input1.1.txt");
    ofstream ofs(
            "/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/output1.1.txt");

    vector<double> x;
    vector<double> y;

    // 数据输入
    int n;
    ifs >> n; // X 和 Y 两数组的长度
    for (int i = 0; i < n; i++) {
        double t;
        ifs >> t;
        x.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        double t;
        ifs >> t;
        y.push_back(t);
    }

    // 输入保证是已排序的
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    // 查找中位数并输出结果
    cout << findMedianSortedArrays1(x, y) << endl;
    cout << findMedianSortedArrays2(x, y) << endl;
    ofs << findMedianSortedArrays2(x, y);

    closeFileStream(ifs, ofs); // 关闭文件输入输出流
    return 0;
}