#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::cin;

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class Element {
public:
    string txt;
    Element *pre_node;
    Element *next_node;
};

Element* newNode(string s, Element *old){
    Element* node = new Element;
    node->txt = s;
    if (old != NULL){
        old->pre_node = node;
    }
    node->next_node = old;
    return node;
}

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    list<string> *elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        unsigned long long mod = hash % bucket_count;
        return mod;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems = new list<string>[bucket_count];
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        size_t hash = hash_func(query.s);
        if (query.type == "check") {
            list<string> tmp_list = elems[query.ind];
            for (auto x : tmp_list){
                std::cout << x << " ";
            }
            std::cout << "\n";
        } else {
            if (query.type == "find") {
                list<string> tmp_list = elems[hash];
                if (std::find(tmp_list.begin(), tmp_list.end(), query.s) != tmp_list.end()){
                    writeSearchResult(true);
                } else{
                    writeSearchResult(false);
                }
            } else if (query.type == "add") {
                list<string> *tmp_list = &elems[hash];
                if (std::find(tmp_list->begin(), tmp_list->end(), query.s) == tmp_list->end()){
                   tmp_list->push_front(query.s);
                }
            } else if (query.type == "del") {
                list<string> *tmp_list = &elems[hash];
                auto i = std::find(tmp_list->begin(), tmp_list->end(), query.s);
                if (i != tmp_list->end()){
                    tmp_list->erase(i);
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
