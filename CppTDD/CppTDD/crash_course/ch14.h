//
//  ch14.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <deque>
#include <iterator>

#include "unit_test.h"


// * Testing * //

void test_insert() {
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

void run_all_tests() {
    run_test(test_insert, "test_insert");
}
