#include <iostream>
#include <vector>
#include <string>

using std::vector;
using namespace std;

struct Segment {
    int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
    //sort values, record the segments
    vector<int> sortedIndexes;
    for (int i = 0; i < segments.size(); ++i) {
        string tmpValue = std::to_string(segments[i].start).append(std::to_string(segments[i].end));
        if (sortedIndexes.size() > 0) {
            for (int j = 0; j < sortedIndexes.size(); ++j) {
                string tmpValue2 = std::to_string(segments[sortedIndexes[j]].start).append(std::to_string(segments[sortedIndexes[j]].end));
                if (atoi(tmpValue.c_str()) < atoi(tmpValue2.c_str())){
                    sortedIndexes.insert(sortedIndexes.begin() + j, i);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedIndexes.size() - 1) {
                        sortedIndexes.insert(sortedIndexes.end(), i);
                        break;
                    }
                }
            }
        } else{
            sortedIndexes.push_back(i);
        }
    }

    //group the segments base on the sorted segments, then get the end point from connections;
    vector<int> connectionPoints;
    Segment connection = {0,0};
    while (sortedIndexes.size() > 0){
        if (connection.start == 0  && connection.end == 0){
            //new loop
            connection = segments[sortedIndexes[0]];
            sortedIndexes.erase(sortedIndexes.begin());
        } else{
            Segment tmpSegment1 = segments[sortedIndexes[0]];
            int start = tmpSegment1.start > connection.start ? tmpSegment1.start : connection.start;
            int end = tmpSegment1.end > connection.end ? connection.end : tmpSegment1.end;
            //it means two segment have common points
            if (end >= start){
                connection.start = start;
                connection.end = end;
                sortedIndexes.erase(sortedIndexes.begin());
                if (sortedIndexes.size() == 0){
                    connectionPoints.push_back(connection.end);
                }
            } else{
                connectionPoints.push_back(connection.end);
                // it means two point are not joint, so need to go to the new loop
                if (sortedIndexes.size() > 0) {
                    connection.start = segments[sortedIndexes[0]].start;
                    connection.end = segments[sortedIndexes[0]].end;
                }

            }
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
        if (i == points.size() - 1){
            std::cout << points[i];
        } else{
            std::cout << points[i] << " ";
        }
    }
}
