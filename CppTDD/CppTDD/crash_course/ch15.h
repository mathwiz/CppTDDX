//
//  ch15.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <string>
#include <cstdio>

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

void test_c_string() {
    std::string word("inconfessable");
    auto cstr = word.c_str();
    assert_that(cstr[0] == 'i', "1");
    assert_that(cstr[1] == 'n', "2");
    assert_that(cstr[word.length() - 1] == 'e', "3");
    assert_that(cstr[word.length()] == '\0', "4");
}

void test_c_string2() {
    std::string word("consciousness");
    printf("c_str: %s at %p\n", word.c_str(), word.c_str());
    printf(" data: %s at %p\n", word.data(), word.data());
    assert_that(true, "no test");
}

void test_comparision() {
    using namespace std::literals::string_literals;
    std::string word("allusion");
    assert_that(word == "allusion", "1");
    assert_that(word == "allusion"s, "2");
    assert_that(word != "Allusion"s, "3");
    assert_that(word < "illusion", "4");
    assert_that(word < "illusion"s, "5");
    assert_that(word > "Allusion"s, "6");
}

void test_append() {
    std::string word("butt");
    word.push_back('e');
    assert_that(word == "butte", "1");
    word += "rfinger";
    assert_that(word == "butterfinger", "2");
    word.append(1, 's');
    assert_that(word == "butterfingers", "3");
    assert_that(std::string(word, 0, 4).append("stockings", 5) == "buttstock", "4");
    std::string other("onset");
    word.append(other.begin(), other.begin() + 2);
    assert_that(word == "butterfingerson", "5");
}

void test_remove() {
    std::string word("therein");
    word.pop_back();
    word.pop_back();
    assert_that(word == "there", "1");
    word.clear();
    assert_that(word == "", "2");
    word.append("therein");
    word.erase(word.begin(), word.begin() + 3);
    assert_that(word == "rein", "3");
    word.erase(1, 2);
    assert_that(word == "rn", "4");
}

void test_replace() {
    std::string word("substitution");
    std::string other("innuendo");
    word.replace(word.begin(), word.begin() + 3,
                 other.begin(), other.begin() + 2);
    assert_that(word == "institution", "1");
    word.replace(2, 6, "vers");
    assert_that(word == "inversion", "2");
}

void run_all_tests() {
    run_test(test_constructing, "test_constructing");
    run_test(test_constructing2, "test_constructing2");
    run_test(test_constructing3, "test_constructing3");
    run_test(test_c_string, "test_c_string");
    run_test(test_c_string2, "test_c_string2");
    run_test(test_comparision, "test_comparision");
    run_test(test_append, "test_append");
    run_test(test_remove, "test_remove");
    run_test(test_replace, "test_replace");
}
