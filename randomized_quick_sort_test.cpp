#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

std::pair<int, int> partition3(vector<int> &a, int l, int r) {
    int pivot = a[l];
    int m1 = l;
    int m2 = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < pivot) {
            m1++;
            m2++;
            swap(a[i], a[m2]);
            swap(a[m1], a[m2]);
        } else if (a[i] == pivot) {
            m2++;
            swap(a[i], a[m2]);
        }
    }
    swap(a[m1], a[l]);
    return std::make_pair(m1, m2);
}

int partition2(vector<int> &a, int l, int r) {
    int pivot = a[l];
    int m = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= pivot) {
            m++;
            swap(a[i], a[m]);
        }
    }
    swap(a[m], a[l]);
    return m;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    std::pair<int, int> pair = partition3(a, l, r);

    randomized_quick_sort(a, l, pair.first - 1);
    randomized_quick_sort(a, pair.second + 1, r);

//    int m = partition2(a, l, r);
//
//    randomized_quick_sort(a, l, m - 1);
//    randomized_quick_sort(a, m + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
