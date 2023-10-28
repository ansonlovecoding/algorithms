#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using std::vector;

vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

vector<int> optimal_sequence_dp(int n){
    //three operations: multiply by 2, multiply by 3, or add 1
    int operations[3] = {1,2,3};
    int num = sizeof(operations) / sizeof(operations[0]);
    vector<int> operationNums;
    operationNums.push_back(0);
    operationNums.push_back(1);
    operationNums.push_back(2);
    for (int i = 3; i <= n; ++i) {
        int result = INT_MAX;
        for (int j = 0; j < num; ++j) {
            int tmpRes = 0;
            int operation = operations[j];
            switch (operation){
                case 1:
                {
                    tmpRes = operationNums[i - 1] + 1;
                    break;
                }
                case 2:
                {
                    int mod2 = i % 2;
                    tmpRes = mod2 > 0 ? operationNums[i - mod2] + mod2 : operationNums[i / 2] + 1;
                    break;
                }
                case 3:
                {
                    int mod3 = i % 3;
                    tmpRes = mod3 > 0 ? operationNums[i - mod3] + mod3 : operationNums[i / 3] + 1;
                    break;
                }
            }
            result = min(tmpRes, result);
        }
        operationNums.push_back(result);
    }

    //compute sequence
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        int p = operationNums[n - 1];
        if (n % 3 == 0 && operationNums[n / 3] <= p) {
            n /= 3;
        } else if (n % 2 == 0  && operationNums[n / 2] <= p) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence_dp(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
