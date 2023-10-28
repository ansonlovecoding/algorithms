#include <iostream>
#include <vector>

using namespace std;
using std::vector;

int optimal_weight(int W, const vector<int> &w) {
    //write your code here
    int n = w.size();
    int** weights = new int* [n + 1];

    for (int i = 0; i <= n; ++i) {
        weights[i] = new int[W + 1];
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (i == 0 || j == 0){
                weights[i][j] = 0;
            } else {
                weights[i][j] = weights[i - 1][j];
                if (w[i - 1] <= j){
                    int val = weights[i - 1][j - w[i - 1]] + w[i - 1];
                    if (weights[i][j] < val){
                        weights[i][j] = val;
                    }
                }
            }
        }
    }
    int result = weights[n][W];

    for (int i = 0; i <= n; ++i) {
        delete[] weights[i];
    }
    delete[] weights;

    return result;
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
