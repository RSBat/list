#include "list.h"

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct no_def {
    no_def() = delete;

    explicit no_def(int val) : val(val) {};

    no_def(const no_def&) = default;

    int val;
};

int main() {
    static_assert(std::is_default_constructible<no_def>() == false, "Something is wrong");
    {
        std::cout << "---1---\n\n";

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

        std::cout << "---1---\n\n";
    }

    {
        std::cout << "---2---\n\n";

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
        std::cout << *(std::prev(string_list.end())) << std::endl;

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

        std::cout << "---2---\n\n";
    }

    {
        std::cout << "---3---\n\n";

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

        std::cout << "---3---\n\n";
    }

    {
        std::cout << "---4---\n\n";

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

        nd_list.erase(nd_list.cbegin(), nd_list.cend());

        for (auto val : nd_list) {
            std::cout << "!" << val.val;
        }
        std::cout << std::endl;

        std::cout << "---4---\n\n";
    }

    {
        std::cout << "---5---\n\n";

        list<int> a;
        list<int> b;

        for (int i = 0; i < 10; i++) {
            a.push_back(i);
            b.push_back(i * 100);
        }

        a.splice(++a.cbegin(), b, ++b.cbegin(), --b.cend());

        for (auto val : a) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        a.splice(a.begin(), b, b.begin(), b.end());
        for (auto val : a) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        b.push_back(10);

        // push_back 10
        a.splice(a.end(), b, b.begin(), b.end());
        for (auto val : a) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // move everything before first
        a.splice(a.begin(), a, ++a.begin(), a.end());
        for (auto val : a) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        a.clear();
        for (auto val : a) {
            assert(false);
        }
        std::cout << std::endl;

        std::cout << "---5---\n\n";
    }
    return 0;
}