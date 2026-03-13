//
//  unit_test.h
//  CppTDD
//
//  Created by Yohan Lee on 3/13/26.
//

#include <stdexcept>

constexpr void assert_that(bool stmt, const char* msg) {
    if (!stmt) throw std::runtime_error{ msg };
}
