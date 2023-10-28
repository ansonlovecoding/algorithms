#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::swap;

struct Arrow {
    bool forward;
    bool backward;
    int value;
};

std::pair<int, int> partition3(vector<Arrow> &arrows, int left, int right){
    int pivot = arrows[left].value;
    int m1 = left;
    int m2 = left;
    for (int i = left + 1; i <= right; i++) {
        if (arrows[i].value < pivot) {
            m1++;
            m2++;
            swap(arrows[i], arrows[m2]);
            swap(arrows[m1], arrows[m2]);
        } else if (arrows[i].value == pivot) {
            m2++;
            swap(arrows[i], arrows[m2]);
        }
    }
    swap(arrows[m1], arrows[left]);

    //if the array has equal points, adjust the location of the points with forward or backward
    if (m2 > m1) {
        int forwardIndex = -1;
        int backwardIndex = -1;
        for (int i = m1; i <= m2; ++i) {
            if (arrows[i].forward){
                forwardIndex = i;
            }
            if (arrows[i].backward){
                backwardIndex = i;
            }
        }
        if (forwardIndex != -1){
            swap(arrows[m1], arrows[forwardIndex]);
        }
        if (backwardIndex != -1){
            swap(arrows[m2], arrows[backwardIndex]);
        }
    }

    return std::make_pair(m1, m2);
}

void quickSortingArrows(vector<Arrow> &arrows, int left, int right) {
    if (left >= right) {
        return;
    }

    std::pair<int, int> pair = partition3(arrows, left, right);
    quickSortingArrows(arrows, left, pair.first > 0 ? pair.first - 1 : 0);
    quickSortingArrows(arrows, pair.second + 1, right);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    //write your code here
    //create the new point with forward and back pointers from starts and ends array
    //then join in the points
    vector<Arrow> allPoints;
    for (int start : starts) {
        Arrow arrow = {true, false, start};
        allPoints.push_back(arrow);
    }
    for (int end : ends) {
        Arrow arrow = {false, true, end};
        allPoints.push_back(arrow);
    }
    for (int point : points) {
        Arrow arrow = {false, false, point};
        allPoints.push_back(arrow);
    }

    //sorting allPoints
    quickSortingArrows(allPoints, 0, allPoints.size() - 1);

    //count the contained segments and put in a new array
    std::map<int, int> countResults;
    int num = 0;
    for (int i = 0; i < allPoints.size(); ++i) {
        Arrow arrow = allPoints[i];
        if (arrow.forward){
            num++;
        }
        if (arrow.backward){
            num--;
        }
        if (!arrow.forward && !arrow.backward) {
            countResults[arrow.value] = num;
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
