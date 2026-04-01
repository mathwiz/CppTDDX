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

void set_up() {
}

void run_all_tests() {
    run_test(test_static_array, "test_static_array");
    run_test(test_array_access, "test_array_access");
}

