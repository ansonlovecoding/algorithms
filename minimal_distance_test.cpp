#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <climits>

using std::vector;
using std::string;
using std::pair;
using std::min;
using std::swap;

int partition(vector<int> &x, vector<int> &y, int left, int right, bool isSortByX) {
    int pivot = isSortByX ? x[left] : y[left];
    int m = left;
    for (int i = left; i <= right; ++i) {
        int tmp = isSortByX ? x[i] : y[i];
        if (tmp < pivot) {
            m++;
            swap(x[i], x[m]);
            swap(y[i], y[m]);
        }
    }
    swap(x[left], x[m]);
    swap(y[left], y[m]);
    return m;
}

void quickSort(vector<int> &x, vector<int> &y, int left, int right, bool isSortByX) {
    if (left >= right) return;
    int m = partition(x, y, left, right, isSortByX);
    quickSort(x, y, left, m > 0 ? m - 1 : 0, isSortByX);
    quickSort(x, y, m + 1, right, isSortByX);
}

double findMiniDistance(vector<int> &x, vector<int> &y, int left, int right){
    if (left >= right) {
        return INT_MAX;
    }
    if (left + 1 == right) {
        return fabs(sqrt(pow(x[right] - x[left], 2) + pow(y[right] - y[left], 2)));
    }
    //then dived it by n/2, get the minimum distances as d1 and d2
    int mid = (right - left) / 2;
    double d1 = findMiniDistance(x, y, left, left + mid);
    double d2 = findMiniDistance(x, y, left + mid + 1, right);
    //get minimum(d1,d2) as d, then get the points whose x-distances to the middle are no exceed d
    double d = min(d1, d2);
    vector<int> midX;
    vector<int> midY;
    for (int i = left; i <= right; ++i) {
        if (abs(x[i] - x[mid]) < d) {
            midX.push_back(x[i]);
            midY.push_back(y[i]);
        }
    }
    //sorting these points by y-coordinates, and dived it by n/2, get the minimum distance as d3
    double d3 = INT_MAX;
    quickSort(midX, midY, 0, midX.size() - 1, false);
    for (int i = 0; i < midX.size(); ++i) {
        int k = i + 7 > midX.size() ? midX.size() : i + 7;
        for (int j = i + 1; j < k; ++j) {
            if (midY[j] - midY[i] < d) {
                double tmpD3 = fabs(sqrt(pow(midX[j] - midX[i], 2) + pow(midY[j] - midY[i], 2)));
                d3 = min(d3, tmpD3);
            }
        }
    }
    //return the minimum(d, d3)
    return min(d, d3);
}

double minimal_distance(vector<int> x, vector<int> y) {
    //write your code here
    //sorting by x-coordinates
    quickSort(x, y, 0, x.size() - 1, true);
    //compute the mini distance
    double miniDistance = findMiniDistance(x, y, 0, x.size() - 1);
    return miniDistance;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
