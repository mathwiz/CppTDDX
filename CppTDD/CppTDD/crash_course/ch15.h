//
//  ch15.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <string>

#include "unit_test.h"

// * Testing * //

void test_constructing() {
    std::string cheese;
    assert_that(cheese.empty(), "1");
    std::string motor_club(3, 'A');
    assert_that(motor_club == "AAA", "2");
    
    auto word = "gobbledygook";
    assert_that(std::string(word) == "gobbledygook", "3");
    assert_that(std::string(word, 6) == "gobble", "4");
}

void test_constructing2() {
    std::string word("catawampus");
    assert_that(word == "catawampus", "1");
    assert_that(std::string(std::move(word)) == "catawampus", "2");
    assert_that(word == "", "3");
    
    std::string word2("catawampus2");
    assert_that(std::string(word2, 0, 3) == "cat", "4");
    assert_that(std::string(word2, 4, 6) == "wampus", "5");
}

void test_constructing3() {
    std::string word("stop at embedded\0null");
    assert_that(word == "stop at embedded", "1");
    using namespace std::string_literals;
    auto literal = "don't stop\0now!"s;
    assert_that(literal.length() == 15, "2");
    assert_that(std::string(literal, 11, 4) == "now!", "3");
}

void run_all_tests() {
    run_test(test_constructing, "test_constructing");
    run_test(test_constructing2, "test_constructing2");
    run_test(test_constructing3, "test_constructing3");
}
