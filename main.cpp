#include "list.h"

#include <iostream>
#include <string>
#include <vector>

struct no_def {
    no_def() = delete;

    explicit no_def(int val) : val(val) {};

    no_def(const no_def&) = default;

    int val;
};

int main() {
    list<int> lst;

    for (int i = 0; i < 10; i++) {
        lst.push_back(i);
    }

    for (int i = 9; i >= 0; i--) {
        int j = lst.back();
        std::cout << j << std::endl;
        assert(i == lst.back());
        lst.pop_back();
    }

    list<std::string> string_list;
    string_list.push_front(" ");
    string_list.push_back("world! ");
    string_list.push_back("this is a list ");
    string_list.push_front("hello");
    string_list.push_back("of strings");

    std::cout << (string_list.begin()->back()) << std::endl;
    std::cout << *(string_list.begin()++) << std::endl;
    std::cout << *(++string_list.begin()) << std::endl;
    std::cout << *(--string_list.end()) << std::endl;

    for (const auto& word : string_list) {
        std::cout << word;
    }
    std::cout << std::endl;

    for (auto rit = string_list.rbegin(); rit != string_list.rend(); ++rit) {
        std::cout << *rit;
        std::cout.flush();
    }
    std::cout << std::endl;

    while (!string_list.empty()) {
        std::cout << string_list.front();
        string_list.pop_front();
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

    list<no_def> nd_list;
    list<no_def> swp_list;

    for (int i = 0; i < 15; i++) {
        nd_list.push_back(no_def(i));
        swp_list.push_back(no_def(i * 100));
    }

    auto cpy = nd_list;

    swap(nd_list, swp_list);

    for (auto val : cpy) {
        std::cout << val.val << " ";
    }
    std::cout << std::endl;

    for (auto val : nd_list) {
        std::cout << val.val << " ";
    }
    std::cout << std::endl;

    return 0;
}