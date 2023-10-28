#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(const vector<Node>& tree, vector<Node>& result, int i){
    Node node = tree[i];
    int left_index = node.left;
    int right_index = node.right;
    if (left_index != -1){
        in_order_traversal(tree, result, left_index);
    }
    result.push_back(node);
    if (right_index != -1){
        in_order_traversal(tree, result, right_index);
    }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    // Implement correct algorithm here
    if (tree.empty())
        return true;
    vector<Node> in_order_keys;
    in_order_traversal(tree, in_order_keys, 0);
    Node *max_node = NULL;
    for (int i = 0; i < in_order_keys.size(); ++i) {
        if (max_node != NULL){
            if (in_order_keys[i].key > max_node->key){
                max_node = &in_order_keys[i];
            } else if (in_order_keys[i].key == max_node->key){
                if (in_order_keys[i].left != -1 && tree[in_order_keys[i].left].key == max_node->key){
                    return false;
                }
            } else{
                return false;
            }
        } else{
            max_node = &in_order_keys[i];
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
