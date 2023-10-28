#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
    //initial the distances for str1 and str2
    unordered_map<string, int> commonSeq;
    int n = a.size();
    int m = b.size();

    commonSeq["0,0"] = 0;
    for (int i = 1; i <= n; ++i) {
        commonSeq[to_string(i) + ",0"] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        string i_str = to_string(i);
        commonSeq["0," + i_str] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int match1 = commonSeq[to_string(i) + "," + to_string(j - 1)];
            int match2 = commonSeq[to_string(i - 1) + "," + to_string(j)];
            int match3 = commonSeq[to_string(i - 1) + "," + to_string(j - 1)];
            if (a[i - 1] == b[j - 1]){
                commonSeq[to_string(i) + "," + to_string(j)] = match3 + 1;
            } else{
                commonSeq[to_string(i) + "," + to_string(j)] = max(match1, match2);
            }
        }
    }
    return commonSeq[to_string(n) + "," + to_string(m)];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
