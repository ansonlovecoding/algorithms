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

struct Point{
    int x;
    int y;
};

bool cmpXY(Point a, Point b) {
    if (a.x != b.x){
        return (a.x < b.x);
    } else{
        return (a.y < b.y);
    }
}

bool cmpY(Point a, Point b) {
    return a.y < b.y;
}

double computeDistance(Point a, Point b){
    return fabs(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

double bruteForce(vector<Point> &points, int left, int right){
    double d = INT_MAX;
    for (int i = left; i <= right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            double tmp = computeDistance(points[i], points[j]);
            d = min(d, tmp);
        }
    }
    return d;
}

double stripClosest(vector<Point> &points){
    //sorting these points by y-coordinates, and dived it by n/2, get the minimum distance as d3
    std::sort(points.begin(), points.end(), cmpY);
    return bruteForce(points, 0, points.size()-1);
}

double findMiniDistance(vector<Point> &points, int left, int right){
    if (right - left <= 2) {
        return bruteForce(points, left, right);
    }
    //then dived it by n/2, get the minimum distances as d1 and d2
    int mid = (right - left) / 2;
    double d1 = findMiniDistance(points, left, left + mid);
    double d2 = findMiniDistance(points, left + mid + 1, right);
    //get minimum(d1,d2) as d, then get the points whose x-distances to the middle are no exceed d
    double d = min(d1, d2);
    vector<Point> midPoints;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - points[mid].x) < d) {
            midPoints.push_back(points[i]);
        }
    }
    double d3 = stripClosest(midPoints);
    //return the minimum(d, d3)
    return min(d, d3);
}

double minimal_distance(vector<int> x, vector<int> y) {
    vector<Point> allpoints;
    for (int i = 0; i < x.size(); ++i) {
        Point point = {x[i], y[i]};
        allpoints.push_back(point);
    }

    //sorting by x-coordinates
    std::sort(allpoints.begin(), allpoints.end(), cmpXY);
    //compute the mini distance
    double miniDistance = findMiniDistance(allpoints, 0, allpoints.size() - 1);
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
