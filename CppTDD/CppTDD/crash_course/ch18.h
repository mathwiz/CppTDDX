//
//  ch18.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//

#include <algorithm>
#include <execution>
#include <string>
#include <vector>

#include "unit_test.h"

using namespace std;

vector<string> words{ "Auntie", "Anne's", "alligator", "Alan", "aegis" };

const auto starts_with_a_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'A' || word[0] == 'a';
};

const auto starts_with_b_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'B' || word[0] == 'b';
};

const auto len_6_pred =
[](const auto& word) {
    return word.length() == 6;
};

void test_all_of() {
    assert_that(all_of(words.cbegin(), words.cend(), starts_with_a_pred), "1");
    assert_that(!all_of(words.cbegin(), words.cend(), len_6_pred), "2");
}

void test_any_of() {

    assert_that(!any_of(words.cbegin(), words.cend(), starts_with_b_pred), "1");
    assert_that(any_of(words.cbegin(), words.cend(), len_6_pred), "2");
}

void run_all_tests() {
    run_test(test_any_of, "test_any_of");
    run_test(test_all_of, "test_all_of");
}
