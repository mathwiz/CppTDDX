//
//  ch13.h
//  CppTDD
//
//  Created by Yohan Lee on 4/1/26.
//

#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <deque>
#include <list>
#include <stack>
#include <bitset>

#include "unit_test.h"

std::array<int, 10> static_array;


// Tests

void test_static_array() {
    assert_that(static_array[0] == 0, "initialized to 0");
    
    std::array<int, 10> local;
    assert_that(local[0] != 0, "not initialized to 0");
    
    std::array<int, 10> local2{ 1, 1, 2, 3 };
    assert_that(local2[0] == 1, "0");
    assert_that(local2[1] == 1, "1");
    assert_that(local2[2] == 2, "2");
    assert_that(local2[3] == 3, "3");
    assert_that(local2[4] == 0, "4");
}

void test_array_access() {
    std::array<int, 4> fib{ 1, 1, 2, 3 };
    
    fib[2] = -1;
    assert_that(fib[2] == -1, "set with []");
    
    fib.at(2) = 2;
    assert_that(fib[2] == 2, "set with at");
    try {
        fib.at(4);
        assert_that(false, "should not get here");
    } catch (std::out_of_range e) {
        assert_that(true, "exception as expected");
    }

    std::get<2>(fib) = -1;
    assert_that(fib[2] == -1, "set with get");
    std::get<2>(fib) = 2;
    assert_that(fib[2] == 2, "set with get");
}

void test_array_ends() {
    std::array<int, 4> fib{ 0, 1, 2, 0 };

    fib.front() = 1;
    assert_that(fib[0] == 1, "set with front");
    assert_that(fib[0] == fib.front(), "get with front");

    fib.back() = 3;
    assert_that(fib[3] == 3, "set with back");
    assert_that(fib[3] == fib.back(), "get with back");
}

void test_array_data() {
    std::array<char, 9> color{ 'o', 'c', 't', 'a', 'r', 'i', 'n', 'e' };
    const auto* color_ptr = color.data();
    
    assert_that(*color_ptr == color[0], "index 0");
    assert_that(color_ptr == &color.front(), "front ref");
    assert_that(color_ptr == &color.at(0), "at ref");
    assert_that(color_ptr == &color[0], "index 0 ref");
}

void test_iterator_empty() {
    std::array<int, 0> e{};
    assert_that(e.begin() == e.end(), "begin equals end");
}

void test_iterators() {
    std::array<int, 3> e{ 1, 2, 3 };
    auto iter = e.begin();
    assert_that(*iter == 1, "1");
    assert_that(iter != e.end(), "not end 1");
    iter++;
    assert_that(*iter == 2, "2");
    assert_that(iter != e.end(), "not end 2");
    iter++;
    assert_that(*iter == 3, "3");
    assert_that(iter != e.end(), "not end 3");
    iter++;
    assert_that(iter == e.end(), "end");
}

void test_array_range() {
    std::array<int, 5> e{ 1, 2, 3, 4, 5 };
    int sum{};
    for (const auto x : e) {
        sum += x;
    }
    assert_that(sum == 15, "ranged sum");
}

void test_vector_construction() {
    std::vector<const char*> vec;
    assert_that(vec.empty(), "default");
    
    std::vector<int> fib{ 1, 1, 2, 3, 5 };
    assert_that(fib[4] == 5, "braced initialization");
}

void test_vector_fill_constructor() {
    std::vector<int> five_nine{ 5, 9 };
    assert_that(five_nine[0] == 5, "braced 0");
    assert_that(five_nine[1] == 9, "braced 1");
    
    std::vector<int> five_nines(5, 9);
    assert_that(five_nines[0] == 9, "constructor 0");
    assert_that(five_nines[4] == 9, "constructor 4");
}

void test_vector_from_iterator() {
    std::array<int, 5> fib{ 1, 1, 2, 3, 5 };
    std::vector<int> vec(fib.begin(), fib.end());
    assert_that(vec[4] == 5, "end");
    assert_that(vec.size() == fib.size(), "size");
}

void test_vector_assign() {
    std::vector<int> message{ 1, 2, 3, 4, 5, 6, 7 };
    assert_that(message[6] == 7, "last");
    message.assign({ 11, 12, 13, 14, 15, 16 });
    assert_that(message[5] = 16, "last");
    assert_that(message.size() == 6, "now one less");
}

void test_vector_insert() {
    std::vector<int> ones(5, 1);
    auto third = ones.begin() + 2;
    ones.insert(third, 2);
    assert_that(ones[0] == 1, "0");
    assert_that(ones[2] == 2, "2");
    assert_that(ones.size() == 6, "one larger");
}

void test_vector_push_back() {
    std::vector<int> ones(3, 1);
    ones.push_back(10);
    assert_that(ones[3] == 10, "at end");
    assert_that(ones.size() == 4, "one larger");
}

void test_vector_emplace() {
    std::vector<std::pair<int, int>> factors;
    factors.emplace_back(2, 30);
    factors.emplace_back(3, 20);
    factors.emplace_back(4, 15);
    factors.emplace(factors.begin(), 1, 60);
    assert_that(factors[0].first == 1, "first");
    assert_that(factors[0].second == 60, "second");
    assert_that(factors[3].first == 4, "first");
    assert_that(factors[3].second == 15, "second");
}

void test_vector_growth() {
    std::vector<std::array<uint8_t, 1024>> kb_store;
    assert_that(kb_store.max_size() > 0, "max size");
    assert_that(kb_store.empty(), "empty");
    
    size_t elements{ 1024 };
    kb_store.reserve(elements);
    assert_that(kb_store.empty(), "empty");
    assert_that(kb_store.capacity() == elements, "capacity");
    
    kb_store.emplace_back();
    kb_store.emplace_back();
    kb_store.emplace_back();
    assert_that(!kb_store.empty(), "not empty");
    assert_that(kb_store.size() == 3, "size");
    
    kb_store.shrink_to_fit();
    assert_that(kb_store.capacity() >= 3, "capacity");

    kb_store.clear();
    assert_that(kb_store.empty(), "empty");
    assert_that(kb_store.capacity() >= 3, "capacity");
}

void test_deque() {
    std::deque<char> d;
    d.push_front('b');
    d.push_back('c');
    d.push_front('z');
    assert_that(d[0] == 'z', "1");
    d.push_back('d');
    d.pop_front();
    d.push_front('a');
    assert_that(d[0] == 'a', "2");
    assert_that(d[1] == 'b', "3");
    assert_that(d[2] == 'c', "4");
    assert_that(d[3] == 'd', "5");
}

void test_list() {
    std::list<int> odds{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    odds.remove_if([](int x) { return x % 2 == 0; });
    auto iter = odds.begin();
    assert_that(*iter == 11, "1");
    iter++;
    assert_that(*iter == 33, "2");
    iter++;
    assert_that(*iter == 55, "3");
    iter++;
    assert_that(*iter == 77, "4");
    iter++;
    assert_that(*iter == 99, "5");
    iter++;
    assert_that(iter == odds.end(), "6");
}

void test_stack() {
    std::vector<int> vec{ 1, 3 };
    std::stack<int, decltype(vec)> stk(vec);
    assert_that(stk.top() == 3, "1");
    stk.pop();
    stk.push(2);
    assert_that(stk.top() == 2, "2");
    stk.pop();
    assert_that(stk.top() == 1, "3");
    stk.pop();
    assert_that(stk.empty(), "4");
}

void test_queue() {
    std::deque<int> deq{ 1, 2 };
    std::queue<int> que(deq);
    assert_that(que.front() == 1, "1");
    assert_that(que.back() == 2, "2");
    que.pop();
    que.push(3);
    assert_that(que.front() == 2, "3");
    assert_that(que.back() == 3, "4");
    que.pop();
    assert_that(que.front() == 3, "5");
    que.pop();
    assert_that(que.empty(), "6");
}

void test_priority_queue() {
    std::priority_queue<double> que;
    que.push(1.0); //1.0
    que.push(2.0); //2.0 1.0
    que.push(1.5); //2.0 1.5 1.0
    assert_value(que.top(), 2.0, 0.0001, "1");
    que.pop();     //1.5 1.0
    que.push(1.1); //1.5 1.1 1.0
    assert_value(que.top(), 1.5, 0.0001, "2");
    que.pop();     //1.1 1.0
    assert_value(que.top(), 1.1, 0.0001, "3");
    que.pop();     //1.0
    assert_value(que.top(), 1.0, 0.0001, "4");
    que.pop();     //
    assert_that(que.empty(), "5");
}

void test_bitset() {
    std::bitset<4> bits{ 0b0101 };
    std::bitset<4> bits2("0101");
    assert_that(bits[0] == true, "1");
    assert_that(bits[1] == false, "2");
    assert_that(bits[2] == true, "3");
    assert_that(bits[3] == false, "4");
    assert_that(bits == bits2, "5");
}

void set_up() {
}

void run_all_tests() {
    run_test(test_static_array, "test_static_array");
    run_test(test_array_access, "test_array_access");
    run_test(test_array_ends, "test_array_ends");
    run_test(test_array_data, "test_array_data");
    run_test(test_iterator_empty, "test_iterator_empty");
    run_test(test_iterators, "test_iterators");
    run_test(test_array_range, "test_array_range");
    run_test(test_vector_construction, "test_vector_construction");
    run_test(test_vector_fill_constructor, "test_vector_fill_constructor");
    run_test(test_vector_from_iterator, "test_vector_from_iterator");
    run_test(test_vector_assign, "test_vector_assign");
    run_test(test_vector_insert, "test_vector_insert");
    run_test(test_vector_push_back, "test_vector_push_back");
    run_test(test_vector_emplace, "test_vector_emplace");
    run_test(test_vector_growth, "test_vector_growth");
    run_test(test_deque, "test_deque");
    run_test(test_list, "test_list");
    run_test(test_stack, "test_stack");
    run_test(test_queue, "test_queue");
    run_test(test_priority_queue, "test_priority_queue");
    run_test(test_bitset, "test_bitset");
}

