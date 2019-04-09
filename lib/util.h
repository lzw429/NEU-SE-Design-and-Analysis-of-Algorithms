//
// Created by 舒意恒 on 2019/4/4.
//

#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_UTIL_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_UTIL_H

#include <cstring>

using namespace std;

// 函数声明

ifstream openIfs(const string &);

inline void closeFileStream(ifstream &, ofstream &);

// 函数实现

ifstream openIfs(const string &inFileName) {
    ifstream ifs(inFileName);
    if (!ifs) {
        throw ios_base::failure("[Error] cannot open the file " + inFileName + " .");
    }
    return ifs;
}

inline void closeFileStream(ifstream &ifs, ofstream &ofs) {
    ifs.close();
    ofs.close();
}

template<class T>
void print(const vector<T> &vec) {
    if (vec.empty())
        cout << "empty";
    else
        for (int i = 0; i < vec.size(); i++)
            cout << vec[i] << " ";
    cout << endl;
}

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_UTIL_H
