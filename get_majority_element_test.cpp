#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

vector<int> sortSequences(vector<int> &a){
    vector<int> sortedSequences;
    for (int i = 0; i < a.size(); ++i) {
        int tmpEndPoint = a[i];
        if (sortedSequences.size() > 0) {
            for (int j = 0; j < sortedSequences.size(); ++j) {
                int tmpValue2 = sortedSequences[j];
                if (tmpEndPoint < tmpValue2){
                    sortedSequences.insert(sortedSequences.begin() + j, tmpEndPoint);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedSequences.size() - 1) {
                        sortedSequences.push_back(tmpEndPoint);
                        break;
                    }
                }
            }
        } else{
            sortedSequences.push_back(tmpEndPoint);
        }
    }
    return sortedSequences;
}

int get_majority_element(vector<int> &a, int left, int right) {
    vector<int> sortedSequences = sortSequences(a);
    int midIndex = (right - left)/2;
    if (sortedSequences[midIndex] != sortedSequences[left] && sortedSequences[midIndex] != sortedSequences[right]){
        return 0;
    }
    return 1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << get_majority_element(a, 0, a.size()) << '\n';
}
