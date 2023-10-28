#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int> &A) {
    //write your code here
    int total = 0;
    for (int num: A) {
        total += num;
    }
    int mod = total % 3;
    if (mod != 0) {
        return 0;
    }

    int capacity = total / 3;
    int n = A.size();

    int results[capacity + 1][n + 1];
    bool parts[capacity + 1][n + 1];

    for (int i = 0; i <= capacity; ++i) {
        for (int j = 0; j <= n; ++j) {
            parts[i][j] = false;
            if (i == 0 || j == 0) {
                results[i][j] = 0;
            } else {
                results[i][j] = results[i][j - 1];
                if (i >= A[j - 1]){
                    int val = results[i - A[j - 1]][j - 1] + A[j - 1];
                    if (results[i][j] <= val) {
                        results[i][j] = val;
                        if (val == capacity)
                            parts[i][j] = true;
                    }
                }
            }
        }
    }

    int num = 0;
    for (int i = 0; i <= n; ++i) {
        if (parts[capacity][i]){
            num++;
        }
    }

    return num >= 3 ? 1 : 0;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
