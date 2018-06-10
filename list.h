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
        std::unique_ptr<T> data; // node owns object
        std::unique_ptr<node> next; // node owns next node
        node* prev; // always valid because we are owned by someone

        node() : data(nullptr), next(nullptr), prev(nullptr) {};
        explicit node(const T& data) : data(std::make_unique<T>(data)), next(nullptr), prev(nullptr) {};
    };

    template <bool b, typename T1, typename T2>
    struct template_if {};

    template <typename T1, typename T2>
    struct template_if<true, T1, T2> { using type = T1; };

    template <typename T1, typename T2>
    struct template_if<false, T1, T2> { using type = T2; };


    template <bool is_const>
    struct iterator_impl {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = size_t;
        using pointer = typename template_if<is_const, const T*, T*>::type;
        using reference = typename template_if<is_const, const T&, T&>::type;
        using value_type = T;

        iterator_impl() = default;
        explicit iterator_impl(node* ptr) : ptr(ptr) {}

        iterator_impl operator++(int) {
            iterator_impl tmp = *this;
            ptr = (ptr->next).get();
            return tmp;
        }

        iterator_impl& operator++() {
            ptr = (ptr->next).get();
            return *this;
        }

        iterator_impl operator--(int) {
            iterator_impl tmp = *this;
            ptr = ptr->prev;
            return tmp;
        }

        iterator_impl operator--() {
            ptr = ptr->prev;
            return *this;
        }

        reference operator*() const {
            return *(ptr->data);
        }

        pointer operator->() const {
            return (ptr->data).get();
        }

        bool operator==(const iterator_impl& b) {
            return ptr == b.ptr;
        }

        bool operator!=(const iterator_impl& b) {
            return !(*this == b);
        }

    private:
        node* ptr;
    };

    std::unique_ptr<node> head;
    node* tail;
    size_t sz;

public:
    using iterator = iterator_impl<false>;
    using const_iterator = iterator_impl<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    list() : head(nullptr), tail(nullptr), sz(0) {}

    list(const list<T>& other) :list() {
        for (const auto& val : other) { this->push_back(val); }
    }

    list& operator=(const list<T>& other) {
        clear();
        for (const auto& val : other) { this->push_back(val); }
    }

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

        return *(tail->prev->data);
    }

    const T& back() const {
        assert(sz != 0);
        // same as assert(tail != nullptr && tail->prev != nullptr);

        return *(tail->prev->data);
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

        return *(head->data);
    }

    const T& front() const {
        assert(sz != 0);

        return *(head->data);
    }

    bool empty() const {
        return sz == 0;
    }

    size_t size() const {
        return sz;
    }

    void clear() {
        if (sz == 0) { return; }
        head = std::move(tail->prev->next);
        sz = 0;
    }

    iterator begin() const {
        return iterator(head.get());
    }

    iterator end() const {
        return iterator(tail);
    }

    const_iterator cbegin() const {
        return const_iterator(head.get());
    }

    const_iterator cend() const {
        return const_iterator(tail);
    }

    reverse_iterator rbegin() const {
        return std::make_reverse_iterator(end());
    }

    reverse_iterator rend() const {
        return std::make_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const {
        return std::make_reverse_iterator(cend());
    }

    const_reverse_iterator crend() const {
        return std::make_reverse_iterator(cbegin());
    }
};


#endif //LIST_LIST_H
