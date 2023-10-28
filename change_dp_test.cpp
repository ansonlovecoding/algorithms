//
// Created by jetlee168 on 21/09/2023.
//
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int get_change(int m) {
    //write your code here
    //coin denominations are 1, 3 and 4
    int coins[3] = {1, 3, 4};
    vector<int> minNumCoins(m + 1);
    minNumCoins[0] = 0;
    int n = sizeof(coins)/sizeof(coins[0]);
    for (int i = 1; i <= m; ++i) {
        int numCoins = INT_MAX;
        for (int j = 0; j < n; ++j) {
            int coin = coins[j];
            if (i >= coin){
                numCoins = min(numCoins, minNumCoins[i - coin] + 1);
            }
        }
        minNumCoins[i] = numCoins;
    }
    return minNumCoins[m];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
