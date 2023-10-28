#include <iostream>

int get_change(int m) {
    //write your code here
    int coinFirst = 10;
    int coinSecond = 5;
    int coinThird = 1;

    int coinFirstNum = m / coinFirst;
    int m1 = m % coinFirst;

    int coinSecondNum = 0;
    int coinThirdNum = 0;
    if (m1 > 0) {
        coinSecondNum = m1 / coinSecond;
        int m2 = m1 % coinSecond;

        if (m2 > 0) {
            coinThirdNum = m2;
        }
    }
    return coinFirstNum + coinSecondNum + coinThirdNum;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
