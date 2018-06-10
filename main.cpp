#include "list.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    list<int> lst;

    for (int i = 0; i < 10; i++) {
        lst.push_back(i);
    }

    for (int i = 9; i >= 0; i--) {
        int j = lst.back();
        std::cout << j << std::endl;
        //assert(i == lst.back());
        lst.pop_back();
    }

    list<std::string> string_list;
    string_list.push_front(" ");
    string_list.push_back("world! ");
    string_list.push_back("this is a list ");
    string_list.push_front("hello");
    string_list.push_back("of strings");

    while (!string_list.empty()) {
        std::cout << string_list.front();
        string_list.pop_front();
    }

    return 0;
}