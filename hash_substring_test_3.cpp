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

ull pre_compute_hashes(const string text, const string pattern, ull p, ull x, ull pre_hash, int position) {
    ull y = 1;
    for (int i = y; i <= pattern.length(); ++i) {
        y = (y * x) % p;
    }
    ull hash = (x * pre_hash % p + text[position] - y * text[position + pattern.length()] % p) % p;
    return hash;
}

std::vector<int> get_occurrences_fast(const Data& input) {
    ull p = 79;
    ull x = 1 + rand() % p;
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    ull p_hash = poly_hash(s, 0, s.length(), p, x);
    ull pre_hash = 0;
    for (int i = t.length() - s.length(); i >= 0; --i) {
        if (pre_hash == 0){
            pre_hash = poly_hash(t, t.length() - s.length(), s.length(), p, x);
        } else{
            pre_hash = pre_compute_hashes(t, s, p, x, pre_hash, i);
        }
        if (pre_hash != p_hash){
            continue;
        }
        if (std::equal(t.begin() + i, t.begin() + i + s.length() - 1, input.pattern.begin())){
            ans.push_back(i);
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences_fast(read_input()));
    return 0;
}
