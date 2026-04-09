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
#include <iostream>


#include "unit_test.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& s, vector<T> v) {
    for (const auto& element : v)
        s << element << ", ";
    return s;
}

// * Testing * //

vector<string> words{ "Auntie", "Anne's", "alligator", "Alan", "aegis" };

const auto starts_with_a_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'A' || word[0] == 'a';
};

const auto starts_with_cap_a_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'A';
};

const auto starts_with_b_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'B' || word[0] == 'b';
};

const auto starts_with_c_pred =
[](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'C' || word[0] == 'c';
};

const auto len_1_pred =
[](const auto& word) {
    return word.length() == 1;
};

const auto len_2_pred =
[](const auto& word) {
    return word.length() == 2;
};

const auto len_3_pred =
[](const auto& word) {
    return word.length() == 3;
};

const auto len_4_pred =
[](const auto& word) {
    return word.length() == 4;
};

const auto len_5_pred =
[](const auto& word) {
    return word.length() == 5;
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

void test_none_of() {
    assert_that(none_of(words.cbegin(), words.cend(), starts_with_b_pred), "1");
    assert_that(none_of(words.cbegin(), words.cend(), len_1_pred), "2");
}

void test_for_each() {
    size_t num_As{};
    const auto count_As =
    [&num_As](const auto& word) {
        if (!word.empty() && word[0] == 'A') ++num_As;
    };

    for_each(words.cbegin(), words.cend(), count_As);
    assert_that(3 == num_As, "1");
}

void test_for_each2() {
    vector<string> results;
    const auto append_star =
    [&results](const auto& word) {
        string elem(word);
        elem.push_back('*');
        results.push_back(elem);
    };

    for_each(words.cbegin(), words.cend(), append_star);
    cout << results << endl;
}

void test_find() {
    const auto f1 = find(words.cbegin(), words.cend(), "Alan");
    assert_that("Alan" == *f1, "1");
    const auto f2 = find_if(words.cbegin(), words.cend(), len_4_pred);
    assert_that("Alan" == *f2, "2");
    const auto f3 = find_if_not(words.cbegin(), words.cend(), len_6_pred);
    assert_that("alligator" == *f3, "3");
}

void test_count() {
    const auto f1 = count(words.cbegin(), words.cend(), "Alan");
    assert_that(1 == f1, "1");
    const auto f2 = count_if(words.cbegin(), words.cend(), len_6_pred);
    assert_that(2 == f2, "2");
    const auto f3 = count_if(words.cbegin(), words.cend(), starts_with_cap_a_pred);
    assert_that(3 == f3, "3");
}

void run_all_tests() {
    run_test(test_count, "test_count");
    run_test(test_find, "test_find");
    //test_for_each2();
    run_test(test_for_each, "test_for_each");
    run_test(test_none_of, "test_none_of");
    run_test(test_any_of, "test_any_of");
    run_test(test_all_of, "test_all_of");
}
