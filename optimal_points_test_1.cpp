#include <iostream>
#include <vector>
#include <string>

using std::vector;
using namespace std;

struct Segment {
    int start, end;
};

vector<int> sortEndpoints(vector<Segment> &segments){
    vector<int> endpoints;
    for (int i = 0; i < segments.size(); ++i) {
        int tmpEndPoint = segments[i].end;
        if (endpoints.size() > 0) {
            for (int j = 0; j < endpoints.size(); ++j) {
                int tmpValue2 = endpoints[j];
                if (tmpEndPoint < tmpValue2){
                    endpoints.insert(endpoints.begin() + j, tmpEndPoint);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == endpoints.size() - 1) {
                        endpoints.push_back(tmpEndPoint);
                        break;
                    }
                }
            }
        } else{
            endpoints.push_back(tmpEndPoint);
        }
    }
    return endpoints;
}

vector<int> optimal_points(vector<Segment> &segments) {
    // sort the endpoints
    vector<int> endpoints = sortEndpoints(segments);

    //group the segments base on the sorted segments, then get the end point from connections;
    vector<int> connectionPoints;
    while (endpoints.size() > 0){
        int endPoint = endpoints[0];
        int count = segments.size();
        int hitCount = 0;
        while (count > 0){
            count--;
            Segment tmpSeg = segments[count];
            if (tmpSeg.start <= endPoint && tmpSeg.end >= endPoint){
                hitCount++;
                segments.erase(segments.begin() + count);
                endpoints = sortEndpoints(segments);
            }
        }
        if (hitCount > 0){
            connectionPoints.push_back(endPoint);
        }
    }
    return connectionPoints;
}




int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
