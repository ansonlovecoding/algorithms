#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
            type(type),
            position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        Bracket bracket = Bracket(next, position + 1);

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(bracket);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()){
                std::cout << bracket.position << '\n';
                return 0;
            } else{
                bool is_matched = opening_brackets_stack.top().Matchc(next);
                if (is_matched){
                    opening_brackets_stack.pop();
                } else{
                    std::cout << bracket.position << '\n';
                    return 0;
                }
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty()){
        std::cout << "Success" << '\n';
    } else{
        int size = opening_brackets_stack.size();
        for (int i = 0; i < size - 1; ++i) {
            opening_brackets_stack.pop();
        }
        std::cout << opening_brackets_stack.top().position << '\n';
    }

    return 0;
}
