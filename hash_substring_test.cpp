#include <iostream>
#include <string>
#include <vector>

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

size_t poly_hash(const string& s, int position, int length, long long p, long long x) {
    unsigned long long hash = 0;
    for (int i = position + length - 1; i >= position; --i)
        hash = (hash * x + s[i]) % p;
    return hash;
}

long long * pre_compute_hashes(const Data& input, long long p, long long x) {
    unsigned long long _T = input.text.length();
    unsigned long long _P = input.pattern.length();
    long long * H = new long long [_T - _P + 1];
    for (int i = 0; i < _T - _P + 1; ++i) {
        H[i] = i;
    }
    H[_T - _P] = poly_hash(input.text, _T - _P, _P, p, x);
    unsigned long long y = 1;
    for (int i = y; i <= _P; ++i) {
        y = (y * x) % p;
    }
    for (int i = _T - _P - 1; i >= 0; --i) {
        unsigned long long tmp_h = H[i + 1];
        int txt_i = input.text[i];
        int txt_p = input.text[i + _P];
        unsigned long long tmp_y = (y * txt_p) % p;
        unsigned long long tmp = ((x * tmp_h % p + txt_i - tmp_y) % p + p) % p;
        H[i] = tmp;
    }
    return H;
}

bool are_equal(string t, int position, string p){
    for (int i = position; i < position + p.length(); ++i) {
        if (t[i] != p[i - position]){
            return false;
        }
    }
    return true;
}

std::vector<int> rabin_karp(const Data& input) {
//    long long p = 10000007;
    long long p = 79;
    long long x = 1 + rand() % p;
    std::vector<int> ans;
    unsigned long long p_hash = poly_hash(input.pattern, 0, input.pattern.length(), p, x);
    long long * H = pre_compute_hashes(input, p, x);
    for (int i = 0; i < input.text.length() - input.pattern.length() + 1; ++i) {
        if (p_hash != H[i]){
            continue;
        }
        if (are_equal(input.text, i, input.pattern)){
            ans.push_back(i);
        }
//        if (input.text.substr(i, input.pattern.length()) == input.pattern){
//            ans.push_back(i);
//        }
    }
    delete[] H;
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(rabin_karp(read_input()));
    return 0;
}
