#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;

double get_optimal_value(int n, int capacity, vector<int> weights, vector<int> values) {
    // write your code here

    //compute the quality first
    double unSortedQuality[n];
    for (int i = 0; i < n; ++i) {
        double tmpQuality = double(values[i]) / double(weights[i]);
        unSortedQuality[i] = tmpQuality;
    }

    //sort the index and the quality from n according to the quality
    vector<int> sortedIndex;
    vector<double> sortedQuality;
    for (int i = 0; i < n; ++i) {
        double tmpQuality = unSortedQuality[i];
        if (sortedQuality.size() > 0) {
            for (int j = 0; j < sortedQuality.size(); ++j) {
                if (tmpQuality < sortedQuality[j]){
                    sortedIndex.insert(sortedIndex.begin() + j, i);
                    sortedQuality.insert(sortedQuality.begin() + j, tmpQuality);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedQuality.size() - 1) {
                        sortedIndex.insert(sortedIndex.end(), i);
                        sortedQuality.insert(sortedQuality.end(), tmpQuality);
                        break;
                    }
                }
            }

        } else{
            sortedIndex.push_back(i);
            sortedQuality.push_back(tmpQuality);
        }

    }

    //using more high quality items
    int leftCapacity = capacity;
    double maximalValue = 0;
    for (int i = 0; i < sortedIndex.size(); ++i) {
        //reverse to get the high quality first
        int j = sortedIndex.size() - i - 1;
        double tmpQuality = sortedQuality[j];
        double tmpIndex = sortedIndex[j];
        int tmpWeight = weights[tmpIndex];
        int tmpValue = values[tmpIndex];

        if (leftCapacity > tmpWeight) {
            maximalValue += tmpValue;
            leftCapacity -= tmpWeight;
        } else {
            maximalValue += leftCapacity * tmpQuality;
            leftCapacity = 0;
        }

        if (leftCapacity == 0) {
            break;
        }

    }

    return maximalValue;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(n, capacity, weights, values);

    std::cout << std::setprecision(4) << std::fixed << optimal_value << std::endl;
    return 0;
}
