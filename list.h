//
// Created by rsbat on 6/10/18.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <memory>
#include <cassert>

template <typename T>
class list {
    struct node {
        std::unique_ptr<T> ptr; // node owns object
        std::unique_ptr<node> next; // node owns next node
        node* prev; // always valid because we are owned by someone

        node() : ptr(nullptr), next(nullptr), prev(nullptr) {};
        explicit node(const T& data) : ptr(std::make_unique<T>(data)), next(nullptr), prev(nullptr) {};
    };

    std::unique_ptr<node> head;
    node* tail;
    size_t sz;

public:
    list() : head(nullptr), tail(nullptr), sz(0) {}

    void push_back(const T& data) {
        if (tail == nullptr) {
            head = std::make_unique<node>();
            tail = head.get();
        }

        std::unique_ptr<node> tmp_node = std::make_unique<node>(data);
        if (sz == 0) {// list is empty
            tmp_node->next = std::move(head);
            head = std::move(tmp_node);
            tail->prev = head.get();
        } else { // we have elements
            node* last = tail->prev;
            tmp_node->next = std::move(last->next);
            tmp_node->prev = last;
            last->next = std::move(tmp_node);
            tail->prev = last->next.get();
        }
        ++sz;
    }

    void pop_back() {
        if (sz == 0) { return; }
        // same as if (tail == nullptr || tail->prev == nullptr) { return; }

        tail->prev = tail->prev->prev;
        if (tail->prev != nullptr) {
            tail->prev->next = std::move(tail->prev->next->next);
        }
        --sz;
    }

    T& back() {
        assert(sz != 0);
        // same as assert(tail != nullptr && tail->prev != nullptr);

        return *(tail->prev->ptr);
    }

    const T& back() const {
        assert(sz != 0);
        // same as assert(tail != nullptr && tail->prev != nullptr);

        return *(tail->prev->ptr);
    }

    void push_front(const T& data) {
        if (tail == nullptr) {
            head = std::make_unique<node>();
            tail = head.get();
        }

        std::unique_ptr<node> tmp_node = std::make_unique<node>(data);
        if (sz == 0) { // list is empty
            tmp_node->next = std::move(head);
            head = std::move(tmp_node);
            tail->prev = head.get();
        } else { // we have elements
            tmp_node->next = std::move(head);
            head = std::move(tmp_node);
            head->next->prev = head.get();
        }
        ++sz;
    }

    void pop_front() {
        if (sz == 0) { return; }

        head = std::move(head->next);
        head->prev = nullptr;
        --sz;

        if (sz == 0) {
            tail->prev = nullptr;
        }
    }

    T& front() {
        assert(sz != 0);

        return *(head->ptr);
    }

    const T& front() const {
        assert(sz != 0);

        return *(head->ptr);
    }

    bool empty() const {
        return sz == 0;
    }

    size_t size() const {
        return sz;
    }
};


#endif //LIST_LIST_H
