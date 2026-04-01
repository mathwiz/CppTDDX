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

void set_up() {
}

void run_all_tests() {
    run_test(test_static_array, "test_static_array");
}

