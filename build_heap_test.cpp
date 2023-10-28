#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        swaps_.clear();
        // The following naive implementation just sorts
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap,
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
        heapsort();
    }

    void heapsort(){
        int n = data_.size();
        vector<int> data_new;
        build_heap();
    }

    void build_heap(){
        int n = data_.size();
        for (int i = n / 2; i >= 0; --i) {
            shift_down(i);
        }
    }

    void shift_down(int i){
        int left_index = 2 * i + 1;
        int right_index = 2 * i + 2;

        if (i >= data_.size()){
            return;
        }

        int num = data_[i];
        int left;
        int smallest = i;
        if (left_index < data_.size()){
            left = data_[left_index];
            if (left < num){
                smallest = left_index;
            }
        }
        if (right_index < data_.size()){
            int right = data_[right_index];
            if (right < left && right < num){
                smallest = right_index;
            }
        }
        if (smallest != i){
            swap(data_[i], data_[smallest]);
            swaps_.push_back(make_pair(i, smallest));
            shift_down(smallest);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
