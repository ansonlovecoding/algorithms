#include <cstdio>
#include <string>
#include <iostream>


class Rope {
public:
//    std::string res;
    char s;
    int key;
    Rope* left;
    Rope* right;
    Rope* parent;

    Rope(char s,int key, Rope* left, Rope* right, Rope* parent)
            : s(s), key(key), left(left), right(right), parent(parent) {}

    std::string result() {
        std::string res;
        in_order(&res, this);
        return res;
    }

    void in_order(std::string* res, Rope* node){
        if (node == NULL){
            return;
        }
        if (node->left != NULL){
            in_order(res, node->left);
        }
        res->append(&node->s);
        if (node->right != NULL){
            in_order(res, node->right);
        }
    }
};

void update(Rope* v) {
    if (v == NULL) return;
//    v->res = (v->left != NULL ? v->left->res : "") + v->s + (v->right != NULL ? v->right->res : "");
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void update_key(Rope* v, int n){
    if (v == NULL || n == 0){
        return;
    }
    v->key += n;
    if (v->left != NULL){
        update_key(v->left, n);
    }
    if (v->right != NULL){
        update_key(v->right, n);
    }
}

void small_rotation(Rope* v) {
    Rope* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Rope* grandparent = v->parent->parent;
    if (parent->left == v) {
        Rope* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Rope* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Rope* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Rope*& root, Rope* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Rope* find(Rope*& root, int key) {
    Rope* v = root;
    Rope* last = root;
    Rope* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Rope* root, int key, Rope*& left, Rope*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
    update_key(right, left != NULL ? -(left->result().length()) : 0);
}

Rope* merge(Rope* left, Rope* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Rope* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Rope* root = NULL;

void insert(int x, char s) {
    Rope* left = NULL;
    Rope* right = NULL;
    Rope* new_rope = NULL;
    split(root, x, left, right);
//    std::string t(1, s);
    if (right == NULL || right->key != x) {
        new_rope = new Rope(s, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_rope), right);
}

void process( int i, int j, int k ) {
    // Replace this code with a faster implementation
    Rope* left = NULL;
    Rope* middle = NULL;
    Rope* right = NULL;
    split(root, i, left, middle);
    split(middle, j - i + 1, middle, right);
    update_key(right, left != NULL ? left->result().length() : 0);
    root = merge(left, right);
    split(root, k, left, right);
    update_key(right, middle != NULL ? middle->result().length() : 0);
    middle = merge(middle, right);
    update_key(middle, left != NULL ? left->result().length() : 0);
    root = merge(left, middle);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.length(); ++i) {
        insert(i, s[i]);
    }
    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index) {
        int i, j, k;
        std::cin >> i >> j >> k;
        process(i, j, k);
    }
    std::cout << root->result() << std::endl;
}
