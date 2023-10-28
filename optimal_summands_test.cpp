#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    if (n < 3) {
        summands.push_back(n);
        return summands;
    }

    //loop maximum n times
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += (i + 1);
        if (sum <= n){
            summands.push_back(i + 1);
        } else{
            int lastSum = sum - (i + 1);
            int lastNum = summands[i - 1] + (n - lastSum);
            summands.pop_back();
            summands.push_back(lastNum);
            break;
        }
    }
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
