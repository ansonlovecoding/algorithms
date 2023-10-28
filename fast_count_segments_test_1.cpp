#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::swap;

int startLabel = 1;
int pointLabel = 2;
int endLabel = 3;

int partition2(vector< std::pair<int, int> > &points, int left, int right){
    int pivot = points[left].first;
    int label = points[left].second;
    int m = left;
    for (int i = left + 1; i <= right; i++) {
        if (points[i].first < pivot || (points[i].first == pivot && points[i].second < label)) {
            m++;
            swap(points[i], points[m]);
        }
    }
    swap(points[m], points[left]);

    return m;
}

void quickSorting(vector< std::pair<int, int> > &points, int left, int right) {
    if (left >= right) {
        return;
    }

    int m = partition2(points, left, right);
    quickSorting(points, left, m > 0 ? m - 1 : 0);
    quickSorting(points, m + 1, right);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    //write your code here
    //create the new point with label from starts and ends array
    //then join in the points
    vector< std::pair<int, int> > allPoints;
    for (int i = 0; i < starts.size(); ++i) {
        allPoints.push_back(std::make_pair(starts[i], startLabel));
        allPoints.push_back(std::make_pair(ends[i], endLabel));
    }
    for (int i = 0; i < points.size(); ++i) {
        allPoints.push_back(std::make_pair(points[i], pointLabel));
    }

    //sorting allPoints
    quickSorting(allPoints, 0, allPoints.size() - 1);

    //count the contained segments and put in a new array
    std::map<int, int> countResults;
    int num = 0;
    for (int i = 0; i < allPoints.size(); ++i) {
        std::pair<int, int> point = allPoints[i];
        if (point.second == startLabel){
            num++;
        }
        if (point.second == endLabel){
            num--;
        }
        if (point.second == pointLabel) {
            countResults[point.first] = num;
        }
    }

    //get the count results and put in the cnt
    for (int i = 0; i < points.size(); ++i) {
        cnt[i] = countResults[points[i]];
    }

    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    //use fast_count_segments
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
