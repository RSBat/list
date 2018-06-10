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

    std::cout << (string_list.begin()->back());

    for (const auto& word : string_list) {
        std::cout << word;
    }
    std::cout << std::endl;

    for (auto rit = string_list.rbegin(); rit != string_list.rend(); ++rit) {
        std::cout << *rit << " ";
        std::cout.flush();
    }
    std::cout << std::endl;

    list<list<std::string>> mlist;
    for (int i = 0; i < 10; i++) {
        list<std::string> tmp;
        for (int j = 0; j < 10; j++) {
            tmp.push_back(std::to_string(i * 10 + j));
        }
        mlist.push_back(tmp);
    }

    for (const auto& tmp : mlist) {
        for (const auto& s : tmp) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}