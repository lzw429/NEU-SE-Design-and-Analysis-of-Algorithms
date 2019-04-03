//
// Created by syh on 19-4-3.
//

// 本题是 LeetCode 4. Median of Two Sorted Arrays
#include <bits/stdc++.h>

using namespace std;

/**
 * 查找两个排序数组中的中位数
 *
 * O(n)解法，合并数组并获取中位数
 * @param nums1 已排序数组1
 * @param nums2 已排序数组2
 * @return 两数组的中位数
 */
double findMedianSortedArrays1(vector<int> &nums1, vector<int> &nums2) {
    int m = nums1.size();
    int n = nums2.size();

    int i = 0, j = 0, size = 0;
    vector<int> nums(m + n, 0);

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
 * O(log_{n})解法，合并数组并获取中位数
 * @param nums1 已排序数组1
 * @param nums2 已排序数组2
 * @return 两数组的中位数
 */
double findMedianSortedArrays2(vector<int> &nums1, vector<int> &nums2) {
    if (nums1.empty() && nums2.empty()) return -1;
    int n1 = nums1.size(), n2 = nums2.size();
    if (n2 < n1) return findMedianSortedArrays2(nums2, nums1);

    int left = 0, right = n1; // begin and end
    int half = (n1 + n2 + 1) >> 1;

    while (left <= right) {
        int m1 = left + ((right - left) >> 1);
        int m2 = half - m1;

        if (m1 < n1 && nums1[m1] < nums2[m2 - 1]) {
            // Too low, so moves right.
            left = m1 + 1;
        } else if (0 < m1 && nums2[m2] < nums1[m1 - 1]) {
            // Too high, so moves left.
            right = m1;
        } else {
            // Found cut.
            int maxleft = m1 == 0 ? nums2[m2 - 1] :
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

/**
 * 找到两数组中第k大的数
 * @param nums1
 * @param m
 * @param num2
 * @param n
 * @param k
 * @return
 */
double findKth(vector<int> &nums1, int m, vector<int> &num2, int n, int k) {

}

int main() {
    ifstream ifs;
    ifs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/input1.1.txt");
    ofstream ofs;
    ofs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/output1.1.txt");

    vector<int> x;
    vector<int> y;

    // 数据输入
    int n;
    ifs >> n; // X 和 Y 两数组的长度
    for (int i = 0; i < n; i++) {
        int t;
        ifs >> t;
        x.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        int t;
        ifs >> t;
        y.push_back(t);
    }
    ifs.close();

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    cout << findMedianSortedArrays1(x, y) << endl;
    cout << findMedianSortedArrays2(x, y) << endl;
    ofs << findMedianSortedArrays2(x, y);
    ofs.close();

    return 0;
}