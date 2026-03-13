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


void run_test(void(*unit_test)(), const char* name) {
    try {
        unit_test();
        printf("[+] Test '%s' successful.\n", name);
    } catch (const std::exception& e) {
        printf("[-] Test failure in '%s'. Exception: %s.\n", name, e.what());
    }
}
