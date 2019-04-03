//
// Created by syh on 19-4-3.
//

#include <bits/stdc++.h>

using namespace std;

string keyword;

class Advertisement {
public:
    string name; // 名称
    int num; // 数量
    string email; // 电子邮件
    string startTime; // 开始时间
    string endTime; // 结束时间

    Advertisement(string name, int num, string email, string startTime, string endTime) :
            name(name), num(num), email(email), startTime(startTime), endTime(endTime) {}
};

bool cmp(Advertisement &a1, Advertisement &a2) {
    if (keyword == "name")
        return a1.name <= a2.name;
    else if (keyword == "num")
        return a1.num <= a2.num;
    else if (keyword == "email")
        return a1.email <= a2.email;
    else if (keyword == "startTime")
        return a1.startTime <= a2.startTime;
    else if (keyword == "endTime")
        return a1.endTime <= a2.endTime;
}

void merge(vector<Advertisement> &advertisements, int l, int mid, int r) {
    int i, j, k;
    int len1 = mid - l + 1;
    int len2 = r - mid;

    // 创建临时数组
    vector<Advertisement> L;
    vector<Advertisement> R;

    // 将数据复制到临时数组
    for (i = 0; i < len1; i++)
        L.push_back(advertisements[l + i]);
    for (j = 0; j < len2; j++)
        R.push_back(advertisements[mid + 1 + j]);

    // 将临时数组归并
    i = j = 0;
    k = l;
    while (i < len1 && j < len2)
        advertisements[k++] = (cmp(L[i], R[j])) ? L[i++] : R[j++];
    while (i < len1)
        advertisements[k++] = L[i++];
    while (j < len2)
        advertisements[k++] = R[j++];
}

void mergeSort(vector<Advertisement> &advertisements, const string &keyword) {
    const int n = advertisements.size() - 1;
    // step 为组内元素个数，step / 2 为左子区间元素个数
    for (int step = 2; step / 2 <= advertisements.size(); step *= 2) {
        for (int i = 0; i < n; i += step) {
            int mid = i + step / 2 - 1;
            if (mid + 1 <= n) { // 存在右子区间
                merge(advertisements, i, mid, min(i + step - 1, n));
            }
        }
    }
}

int main() {
    ifstream ifs;
    ifs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/input1.3.txt");
    ofstream ofs;
    ofs.open("/run/media/syh/0D11080D0D11080D/workspace/NEU-SE-Design-and-Analysis-of-Algorithms/exp1/output1.3.txt");

    vector<Advertisement> advertisements;
    // 数据输入
    string name;
    int num;
    string email, startTime, endTime;
    while (ifs >> name) {
        if (name == "name" || name == "num" || name == "email" || name == "startTime" || name == "endTime") {
            keyword = name;
            break;
        }

        ifs >> num >> email >> startTime >> endTime;
        Advertisement advertisement(name, num, email, startTime, endTime);
        advertisements.push_back(advertisement);
    }
    ifs.close();

    mergeSort(advertisements, name);

    for (int i = 1; i <= advertisements.size(); i++) {
        ofs << i << endl;
        ofs << "\t" << advertisements[i - 1].name << endl;
        ofs << "\t" << advertisements[i - 1].num << endl;
        ofs << "\t" << advertisements[i - 1].email << endl;
        ofs << "\t" << advertisements[i - 1].startTime << endl;
        ofs << "\t" << advertisements[i - 1].endTime << endl;
    }
    ofs.close();
    return 0;
}
