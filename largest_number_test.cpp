#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool isGreaterOrEqual(string a, string b) {
    string tmpA = a + b;
    string tmpB = b + a;
    if (atoi(tmpA.c_str()) >= atoi(tmpB.c_str())){
        return true;
    } else{
        return false;
    }
}

string largest_number(vector<string> a) {
    //write your code here
    std::stringstream ret;

    vector<string> sortedA;
    for (int i = 0; i < a.size(); ++i) {
        string tmp = a[i];
        if (sortedA.size() > 0) {
            for (int j = 0; j < sortedA.size(); ++j) {
                string tmpValue2 = sortedA[j];
                if (!isGreaterOrEqual(tmp, tmpValue2)){
                    sortedA.insert(sortedA.begin() + j, tmp);
                    break;
                } else{
                    //the element is still greater than the last element, means it is the largest
                    if (j == sortedA.size() - 1) {
                        sortedA.push_back(tmp);
                        break;
                    }
                }
            }
        } else{
            sortedA.push_back(tmp);
        }
    }

    for (size_t i = 0; i < sortedA.size(); i++) {
        ret << sortedA[ sortedA.size() - i - 1];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
