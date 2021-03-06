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

        std::cout << (string_list.begin()->back()) << std::endl; // o
        std::cout << *(string_list.begin()++) << std::endl; // hello
        std::cout << *(++string_list.begin()) << std::endl; //
        std::cout << *(--string_list.end()) << std::endl; // of strings
        std::cout << *(std::prev(string_list.end())) << std::endl; // of strings

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

    {
        list<int> ilist;
        ilist.push_back(10); ilist.push_back(20);
        auto it1 = ilist.begin();
        auto it2 = ilist.cbegin();

        assert(it1 == it2);
        assert(it2 == it1);

        ilist.begin() != ilist.end();
    }

    {
        list<int> ilist;
        auto it = ilist.cend();
        ilist.push_back(5);
        --it;
        std::cout << *it;
    }


    {
        list<double> dlist;
        for (int i = 0; i < 1000; i++) {
            bool b = rand() & 1;
            if (dlist.empty()) { b = true; }
            if(b) {
                dlist.push_back(rand());
            } else {
                dlist.pop_front();
            }
        }
    }

    {
        std::cout << "---splice---\n\n";

        list<int> ilist;
        list<int> ilist2;

        ilist.push_back(1);
        ilist.push_back(2);
        ilist.push_back(3);
        ilist.push_back(4);

        ilist2.push_back(5);
        ilist2.push_back(6);
        ilist2.push_back(7);
        ilist2.push_back(8);

        auto it1 = std::next(ilist.begin(), 2);
        auto it2 = std::next(ilist2.begin());
        auto it3 = std::next(ilist2.begin(), 3);

        ilist.splice(it1, ilist2, it2, it3);

        for (auto i : ilist) {
            std::cout << i << " ";
        }

        std::cout << *it2 << std::endl;

        std::cout << "---splice---\n\n";
    }

    {
        list<int> ilist;
        ilist.push_back(1);
        ilist.push_back(2);
        ilist.push_back(3);
        ilist.push_back(4);

        ilist.clear();

        assert(ilist.empty());
        assert(ilist.begin() == ilist.end());
    }

    {
        list<int> ilist;
        ilist.push_back(1);
        ilist.push_back(2);
        ilist.push_back(3);
        ilist.push_back(4);

        ilist.clear();

        while (!ilist.empty()) {
            ilist.pop_back();
        }

        assert(ilist.empty());
        assert(ilist.begin() == ilist.end());
    }


    {
        list<int> ilist;
        ilist.push_back(1);
        ilist.push_back(2);
        ilist.push_back(3);
        ilist.push_back(4);

        ilist.clear();

        while (!ilist.empty()) {
            ilist.pop_front();
        }

        assert(ilist.empty());
        assert(ilist.begin() == ilist.end());
    }

    return 0;
}