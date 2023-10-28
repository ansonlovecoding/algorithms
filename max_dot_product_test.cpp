#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
    // write your code here
    // sort array a and array b
    vector<int> sortedA;
    vector<int> sortedB;
    for (int i = 0; i < a.size(); ++i) {
        int tmpA = a[i];
        if (sortedA.size() > 0) {
            for (int j = 0; j < sortedA.size(); ++j) {
                if (tmpA < sortedA[j]){
                    sortedA.insert(sortedA.begin() + j, tmpA);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedA.size() - 1) {
                        sortedA.insert(sortedA.end(), tmpA);
                        break;
                    }
                }
            }

        } else{
            sortedA.push_back(tmpA);
        }

    }

    for (int i = 0; i < b.size(); ++i) {
        int tmpB = b[i];
        if (sortedB.size() > 0) {
            for (int j = 0; j < sortedB.size(); ++j) {
                if (tmpB < sortedB[j]){
                    sortedB.insert(sortedB.begin() + j, tmpB);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedB.size() - 1) {
                        sortedB.insert(sortedB.end(), tmpB);
                        break;
                    }
                }
            }

        } else{
            sortedB.push_back(tmpB);
        }

    }

    // compute each of them by a1 * b1, a2 * b2, an * bn
    long long result = 0;
    for (size_t i = 0; i < sortedA.size(); i++) {
        result += ((long long) sortedA[i]) * sortedB[i];
    }
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::cout << max_dot_product(a, b) << std::endl;
}
