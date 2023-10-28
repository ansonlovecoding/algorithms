#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(const vector<Node>& tree, vector<int>& result, int i){
    int key_value = tree[i].key;
    int left_index = tree[i].left;
    int right_index = tree[i].right;
    if (left_index != -1){
        in_order_traversal(tree, result, left_index);
    }
    result.push_back(key_value);
    if (right_index != -1){
        in_order_traversal(tree, result, right_index);
    }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    // Implement correct algorithm here
    if (tree.empty())
        return true;
    vector<int> in_order_keys;
    in_order_traversal(tree, in_order_keys, 0);
    int max = INT_MIN;
    for (int i = 0; i < in_order_keys.size(); ++i) {
        if (in_order_keys[i] > max){
            max = in_order_keys[i];
        } else{
            return false;
        }
    }
    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
