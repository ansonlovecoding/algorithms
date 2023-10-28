#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    //initial the distances for str1 and str2
    unordered_map<string, int> commonSeq;
    int n = a.size();
    int m = b.size();
    int o = c.size();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= o; ++k) {
                if (i == 0 || j == 0 || k == 0){
                    commonSeq[to_string(i) + "," + to_string(j) + "," + to_string(k)] = 0;
                } else if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1]){
                    int match4 = commonSeq[to_string(i - 1) + "," + to_string(j - 1) + "," + to_string(k - 1)];
                    commonSeq[to_string(i) + "," + to_string(j) + "," + to_string(k)] = match4 + 1;
                } else{
                    int match1 = commonSeq[to_string(i - 1) + "," + to_string(j) + "," + to_string(k)];
                    int match2 = commonSeq[to_string(i) + "," + to_string(j - 1) + "," + to_string(k)];
                    int match3 = commonSeq[to_string(i) + "," + to_string(j) + "," + to_string(k - 1)];
                    commonSeq[to_string(i) + "," + to_string(j) + "," + to_string(k)] = max(max(match1, match2),match3);
                }
            }
        }
    }
    return commonSeq[to_string(n) + "," + to_string(m) + "," + to_string(o)];
}

int lcsOf3( vector<int> &a, vector<int> &b, vector<int> &c)
{
    int n = a.size();
    int m = b.size();
    int o = c.size();

    int L[n+1][m+1][o+1];

    /* Following steps build L[m+1][n+1][o+1] in
       bottom up fashion. Note that L[i][j][k]
       contains length of LCS of X[0..i-1] and
       Y[0..j-1]  and Z[0.....k-1]*/
    for (int i=0; i<=n; i++)
    {
        for (int j=0; j<=m; j++)
        {
            for (int k=0; k<=o; k++)
            {
                if (i == 0 || j == 0||k==0)
                    L[i][j][k] = 0;

                else if (a[i-1] == b[j-1] && a[i-1]==c[k-1])
                    L[i][j][k] = L[i-1][j-1][k-1] + 1;

                else
                    L[i][j][k] = max(max(L[i-1][j][k],
                                         L[i][j-1][k]),
                                     L[i][j][k-1]);
            }
        }
    }

    /* L[m][n][o] contains length of LCS for
      X[0..n-1] and Y[0..m-1] and Z[0..o-1]*/
    return L[n][m][o];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
    //lcsof3 faster than lcs3
    std::cout << lcsOf3(a, b, c) << std::endl;
}
