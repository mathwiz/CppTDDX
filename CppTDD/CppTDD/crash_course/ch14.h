//
//  ch14.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <iterator>
#include <deque>
#include <forward_list>

#include "unit_test.h"


// * Testing * //

void test_output_iterators() {
    std::deque<int> dq;
    auto back_ins = std::back_inserter(dq);
    *back_ins = 2; // 2
    ++back_ins;
    *back_ins = 4; // 2 4
    ++back_ins;
    
    auto front_ins = std::front_inserter(dq);
    *front_ins = 1; // 1 2 4
    ++front_ins;
    
    auto gen_ins = std::inserter(dq, dq.begin() + 2);
    *gen_ins = 3; // 1 2 3 4
    ++gen_ins;
    
    assert_that(dq[0] == 1, "1");
    assert_that(dq[1] == 2, "2");
    assert_that(dq[2] == 3, "3");
    assert_that(dq[3] == 4, "4");
}

void test_input_iterators() {
    const std::forward_list<int> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    assert_that(*iter == 1, "1");
    ++iter;
    assert_that(*iter == 2, "2");
    ++iter;
    assert_that(*iter == 3, "3");
    ++iter;
    assert_that(iter == easy_as.end(), "4");
}

void run_all_tests() {
    run_test(test_output_iterators, "test_output_iterators");
    run_test(test_input_iterators, "test_input_iterators");
}
