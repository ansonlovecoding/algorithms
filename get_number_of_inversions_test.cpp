#include <iostream>
#include <vector>

using std::vector;
using std::swap;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (right <= left) {
        if (right == left) {
            b[left] = a[left];
        }
        return number_of_inversions;
    }
    if (right == left + 1) {
        b[left] = a[left];
        b[right] = a[right];
        if (a[left] > a[right]) {
            number_of_inversions++;
            swap(b[left],b[right]);
        }
        return number_of_inversions;
    }
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave + 1, right);

    //merging and sorting two parts
    for (int i = left; i < ave + 1; ++i) {
        int value = b[i];
        int index = i;
        for (int j = ave + 1; j < right + 1; ++j) {
            if (value > b[j]) {
                number_of_inversions++;
                swap(b[index], b[j]);
                index = j;
            }
        }
    }

    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size() - 1) << '\n';
}
