//
//  ch13.h
//  CppTDD
//
//  Created by Yohan Lee on 4/1/26.
//

#include <array>

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
}

