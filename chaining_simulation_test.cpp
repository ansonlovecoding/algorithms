#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

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
    vector<Element*> elems;
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
        for (int i = 0; i < bucket_count; ++i) {
            elems.push_back(NULL);
        }
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
            Element *el = elems[query.ind];
            while (el != NULL){
                std::cout << el->txt << " ";
                el = el->next_node;
            }
            std::cout << "\n";
        } else {
            if (query.type == "find") {
                Element *el = elems[hash];
                while (el != NULL && el->txt.length() > 0){
                    if (el->txt != query.s){
                        el = el->next_node;
                    } else{
                        writeSearchResult(true);
                        return;
                    }
                }
                writeSearchResult(false);
            } else if (query.type == "add") {
                bool was_found = false;
                Element *old_el = elems[hash];
                Element *el = old_el;
                while (el != NULL){
                    if (el->txt != query.s){
                        el = el->next_node;
                    } else{
                        was_found = true;
                        break;
                    }
                }
                if (!was_found){
                    elems[hash] = newNode(query.s, old_el);
                }
            } else if (query.type == "del") {
                Element *el = elems[hash];
                while (el != NULL){
                    if (el->txt != query.s){
                        el = el->next_node;
                    } else{
                        if (el->pre_node != NULL){
                            el->pre_node->next_node = el->next_node;
                            if (el->next_node != NULL){
                                el->next_node->pre_node = el->pre_node;
                            }
                        } else{
                            el = NULL;
                            elems[hash] = NULL;
                        }
                        break;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
        for (int i = 0; i < elems.size(); ++i) {
            Element *p = elems[i];
            delete p;
        }
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
