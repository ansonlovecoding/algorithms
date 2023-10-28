#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull poly_hash(const string& s, int position, int length, ull p, ull x) {
    ull hash = 0;
    for (int i = position + length - 1; i >= position; --i)
        hash = (hash * x + s[i]) % p;
    return hash;
}

std::vector<int> get_occurrences_fast(const Data& input) {
    ull p = 79;
    ull x = 1 + rand() % p;
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    ull p_hash = poly_hash(s, 0, s.length(), p, x);
    for (int i = 0; i <= t.length() - s.length(); ++i) {
        ull pre_hash = poly_hash(t, i, s.length(), p, x);
        if (pre_hash != p_hash){
            continue;
        }
        if (std::equal(t.begin() + i, t.begin() + i + s.length() - 1, input.pattern.begin())){
            ans.push_back(i);
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences_fast(read_input()));
    return 0;
}
