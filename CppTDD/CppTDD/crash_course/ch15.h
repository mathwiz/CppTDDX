//
//  ch15.h
//  CppTDD
//
//  Created by Yohan Lee on 4/6/26.
//

#include <string>
#include <cstdio>
#include <regex>

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

void test_comparison() {
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
    
    std::string shamp("shamp");
    shamp.resize(4);
    assert_that(shamp == "sham", "3");
    shamp.append("p");
    shamp.resize(7, 'o');
    assert_that(shamp == "shampoo", "4");

    std::string hobbits("hobbits");
    assert_that(hobbits.substr() == "hobbits", "5");
    assert_that(hobbits.substr(3) == "bits", "6");
    assert_that(hobbits.substr(3, 3) == "bit", "7");
}

void test_search() {
    using namespace std::literals::string_literals;
    std::string word("pizzazz");
    assert_that(word.find("zz"s) == 2, "1"); // pi(z)zazz
    assert_that(word.find("zz"s, 3) == 5, "2"); // pizza(z)z
    assert_that(word.find("zaz") == 3, "3"); // piz(zaz)z
    assert_that(word.find('z') == 2, "4");
    assert_that(word.find('x') == std::string::npos, "5");
}

void test_search2() {
    using namespace std::literals::string_literals;
    std::string word("pizzazz");
    assert_that(word.rfind("zz"s) == 5, "1"); // pizza(z)z
    assert_that(word.rfind("zz"s, 3) == 2, "2"); // pi(z)zazz
    assert_that(word.rfind("zaz") == 3, "3"); // piz(zaz)z
    assert_that(word.rfind('z') == 6, "4");
    assert_that(word.rfind('x') == std::string::npos, "5");
}

void test_search3() {
    using namespace std::literals::string_literals;
    std::string word("pizzazzezz");
    assert_that(word.find_first_of("zi"s) == 1, "1");
    assert_that(word.find_first_of("ie"s, 3) == 7, "2");
    assert_that(word.find_first_of("za") == 2, "3");
    assert_that(word.find_first_of('a') == 4, "4");
    assert_that(word.find_first_of('x') == std::string::npos, "5");
}

void test_search4() {
    using namespace std::literals::string_literals;
    std::string word("pizzazzezz pez");
    assert_that(word.find_last_of("pi"s) == 11, "1");
    assert_that(word.find_first_not_of("za"s, 3) == 7, "2");
    assert_that(word.find_first_not_of("piza") == 7, "3");
    assert_that(word.find_last_of('e') == 12, "4");
    assert_that(word.find_last_of('x') == std::string::npos, "5");
}

void test_conversion() {
    using namespace std::literals::string_literals;
    assert_that("8675309"s == std::to_string(8675309), "1");
    assert_that(L"90210"s == std::to_wstring(90210), "2");
    
    assert_that(8675309 == std::stoi("8675309"), "3");
    size_t last_character{};
    assert_that(0x1e == std::stoul("0x1e"s, &last_character, 16), "4");
    assert_that(last_character == 4, "5");
    assert_value(std::stod("3.14"), 3.14, 0.001, "6");
}

void test_string_view() {
    std::string_view empty;
    assert_that(empty.data() == nullptr, "1");
    assert_that(empty.size() == 0, "2");
    assert_that(empty.empty(), "3");
    
    std::string word("ambidextrous");
    std::string_view view(word);
    assert_that(view == "ambidextrous", "4");
    
    auto c_string = "gauche";
    std::string_view view_from_c_string(c_string);
    assert_that(view_from_c_string == "gauche", "5");

    auto c_string2 = "sinister";
    std::string_view view_from_c_string_and_length(c_string2, 3);
    assert_that(view_from_c_string_and_length == "sin", "6");
    
    std::string_view view_from_constructor("ambidextrous");
    view_from_constructor.remove_prefix(4);
    assert_that(view_from_constructor == "dextrous", "7");
    view_from_constructor.remove_suffix(4);
    assert_that(view_from_constructor == "dext", "8");
}

void test_regex() {
    std::regex zip_regex{ R"((\w{2})?(\d{5})(-\d{4})?)" };
    assert_that(zip_regex.mark_count() == 3, "1");
    std::smatch results;
    std::string nj("NJ08562-1234");
    
    const auto matched = std::regex_match(nj, results, zip_regex);
    assert_that(matched, "2");
    assert_that(results[0] == "NJ08562-1234", "3");
    assert_that(results[1] == "NJ", "4");
    assert_that(results[2] == "08562", "5");
    assert_that(results[3] == "-1234", "6");
    
    std::string iomega("zip drive");
    const auto matched_iomega = std::regex_match(iomega, results, zip_regex);
    assert_that(!matched_iomega, "7");
}

void run_all_tests() {
    run_test(test_constructing, "test_constructing");
    run_test(test_constructing2, "test_constructing2");
    run_test(test_constructing3, "test_constructing3");
    run_test(test_c_string, "test_c_string");
    run_test(test_c_string2, "test_c_string2");
    run_test(test_comparison, "test_comparison");
    run_test(test_append, "test_append");
    run_test(test_remove, "test_remove");
    run_test(test_replace, "test_replace");
    run_test(test_search, "test_search");
    run_test(test_search2, "test_search2");
    run_test(test_search3, "test_search3");
    run_test(test_search4, "test_search4");
    run_test(test_conversion, "test_conversion");
    run_test(test_string_view, "test_string_view");
    run_test(test_regex, "test_regex");
}
