//
//  ch17.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//

#include <string>
#include <filesystem>

#include "unit_test.h"

using namespace std::filesystem;

void test_path() {
    path empty;
    path shadow{ "/etc/shadow" };
    assert_that(empty.empty(), "1");
    assert_that(shadow == std::string{ "/etc/shadow" }, "2");
}

void run_all_tests() {
    run_test(test_path, "test_path");
}

