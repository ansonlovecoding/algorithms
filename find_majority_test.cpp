#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int countDuplicated(vector<int> &a, int left, int right, int target) {
    if (target == -1) {
        return 0;
    }

    int count = 0;
    for (int i = left; i < right + 1; ++i) {
        if (a[i] == target) {
            count++;
        }
    }
    return count;
}

int find_majority(vector<int> &a, int left, int right) {
    if (left == right){
        // it means only has one element
        return a[left];
    }
    if (left + 1 == right){
        // it means two elements are nearby
        if (a[left] == a[right]){
            return a[left];
        } else {
            return -1;
        }
    }
    // it means it has more than two elements, should be dived
    int mid = (right - left) / 2;
    int mod = (right - left) % 2;
    int leftMajority = find_majority(a, left, left + mid);
    int rightMajority = find_majority(a, left + mid + 1, right);
    if (leftMajority != -1 && rightMajority != -1 && leftMajority == rightMajority){
        //the majority was found
        return leftMajority;
    } else{
        int half = mod > 0 ? mid + 1 : mid;
        int countLeft = countDuplicated(a, left, right, leftMajority);
        if (countLeft > half) {
            return leftMajority;
        }
        int countRight = countDuplicated(a, left, right, rightMajority);
        if (countRight > half) {
            return rightMajority;
        }
    }
    return -1;
}


int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (find_majority(a, 0, a.size() - 1) != -1) << '\n';
}
