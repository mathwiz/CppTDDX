//
//  ch14.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <iterator>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

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

void test_forward_iterators() {
    const std::forward_list<int> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    auto iter2{ iter };
    int sum{};
    while (iter != easy_as.end())
        sum += *(iter++);
    
    while (iter2 != easy_as.end())
        sum += *(iter2++);

    assert_that(sum == 12, "1");
}

void test_bidirectional_iterators() {
    const std::list<int> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    assert_that(*iter == 1, "1");
    ++iter;
    assert_that(*iter == 2, "2");
    --iter;
    assert_that(*iter == 1, "3");
    assert_that(iter == easy_as.cbegin(), "4");
}

void test_random_access_iterators() {
    const std::vector<int> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    assert_that(iter[0] == 1, "1");
    ++iter;
    assert_that(*(easy_as.cbegin() + 2) == 3, "2");
    assert_that((easy_as.cend() - iter) == 2, "3");
}

void test_mutable_iterators() {
    std::deque<int> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    assert_that(iter[0] == 1, "1");
    iter[1] = 0;
    assert_that(iter[1] == 0, "2");
}

void test_iterator_advance() {
    const std::vector<int> data{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    };
    auto iter = data.begin();
    assert_that(*iter == 1, "1");
    std::advance(iter, 4);
    assert_that(*iter == 5, "2");
    std::advance(iter, 4);
    assert_that(*iter == 9, "3");
    std::advance(iter, -8);
    assert_that(*iter == 1, "4");
}

void test_iterator_next_prev() {
    const std::vector<int> data{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    };
    auto iter = data.begin();
    assert_that(*iter == 1, "1");
    std::advance(iter, 4);
    assert_that(*iter == 5, "2");
    
    auto iter2 = std::next(iter);
    assert_that(*iter2 == 6, "3");
    
    auto iter3 = std::next(iter, 4);
    assert_that(*iter3 == 9, "4");
    
    assert_that(*iter == 5, "5");
}

void run_all_tests() {
    run_test(test_output_iterators, "test_output_iterators");
    run_test(test_input_iterators, "test_input_iterators");
    run_test(test_forward_iterators, "test_forward_iterators");
    run_test(test_bidirectional_iterators, "test_bidirectional_iterators");
    run_test(test_random_access_iterators, "test_random_access_iterators");
    run_test(test_mutable_iterators, "test_mutable_iterators");
    run_test(test_iterator_advance, "test_iterator_advance");
    run_test(test_iterator_next_prev, "test_iterator_next_prev");
}
