#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using std::string;

int edit_distance(const string &str1, const string &str2) {
    //initial the distances for str1 and str2
    unordered_map<string, int> distances;
    int n = str1.length();
    int m = str2.length();

    distances["0,0"] = 0;
    for (int i = 1; i <= n; ++i) {
        distances[to_string(i) + ",0"] = i;
    }
    for (int i = 1; i <= m; ++i) {
        string i_str = to_string(i);
        distances["0," + i_str] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int insertion = distances[to_string(i) + "," + to_string(j - 1)] + 1;
            int deletion = distances[to_string(i - 1) + "," + to_string(j)] + 1;
            int match = distances[to_string(i - 1) + "," + to_string(j - 1)];
            int mismatch = distances[to_string(i - 1) + "," + to_string(j - 1)] + 1;
            if (str1.at(i - 1) == str2.at(j - 1)){
                int min_distance = min(min(insertion, deletion),match);
                distances[to_string(i) + "," + to_string(j)] = min_distance;
            } else{
                int min_distance = min(min(insertion, deletion),mismatch);
                distances[to_string(i) + "," + to_string(j)] = min_distance;
            }
        }
    }
    return distances[to_string(n) + "," + to_string(m)];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
